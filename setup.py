#!/usr/bin/env python3

"""This is the main builder and installer for the timedata DSP Python
extension."""

import sys
sys.path.append('src/py')

from timedata_build import arguments, generate

OPTS = '-flto -fno-math-errno -fomit-frame-pointer -funroll-loops -ffast-math'

"""Each of these "flags" corresponds to an environment variables looking like
   TIMEDATA_$NAME where $NAME is the uppercase version of flag.

   For example, to run generate with the "tiny" flag, enter:

       TIMEDATA_TINY=true ./setup.py generate
"""
FLAGS = arguments.extract_env(
    benchmark='lists',
    benchmark_size=10240,
    benchmark_number=1000,
    buildtype='o3',
    compileropt=OPTS,
    name='',
    tiny=False,
    models=''
    )

sys.argv[1:] = arguments.insert_dependencies(
    sys.argv[1:],

    develop='generate',
    build_sphinx='develop',
    test='develop',
    )

print('Building targets', *sys.argv[1:])

BUILD_OPTIONS = dict(
    o2=['-O2', '-DNDEBUG'],
    o3=['-O3', '-DNDEBUG'],
    debug=['-O0', '-DDEBUG'],
    )

"""See http://ithare.com/c-performance-common-wisdoms-and-common-wisdoms/
Other possibilities include:
    -ffast-math
    -flto
    -fno-math-errno
    -fomit-frame-pointer
    -fprofile-generate
    -ftree-vectorize
    -funroll-loops
"""


import datetime, glob, os, platform, re, shutil, subprocess, unittest
import setuptools.extension
from setuptools.command.build_ext import build_ext as _build_ext


LEAST_PYTHON = 3, 4
ACTUAL_PYTHON = sys.version_info[:2]

assert ACTUAL_PYTHON >= LEAST_PYTHON, (
    'Must use at least Python %d.%d but have version %d.%d' %
    (LEAST_PYTHON[0], LEAST_PYTHON[1], ACTUAL_PYTHON[0], ACTUAL_PYTHON[1]))

# Uncomment this next line if you want Cython to output HTML showing how C++-ey
# it can make your code.
# Same as --annotate here: http://docs.cython.org/src/quickstart/cythonize.html
#
# import Cython.Compiler.Options
# Cython.Compiler.Options.annotate = True

IS_MAC = (platform.system() == 'Darwin')
IS_LINUX = (platform.system() == 'Linux')
IS_DEBIAN = IS_LINUX and (platform.linux_distribution()[0] == 'debian')
IS_WINDOWS = (platform.system() == 'Windows')

LIBRARIES = [] if (IS_MAC or IS_LINUX or IS_WINDOWS) else ['m']

ROOT_DIR = os.path.dirname(os.path.realpath(__file__))

CLEAN_DIRS = ['build']


def execute(command):
    result = os.system(command)
    if result:
        raise Exception('%s\n failed with code %s' % (command, result))


def run(*cmds):
    return subprocess.check_output(cmds).strip().decode('ascii')


def git_tags():
    tags = run('git', 'describe', '--tags', '--always')
    branch = run('git', 'rev-parse', '--abbrev-ref', 'HEAD')
    remote = run('git', 'config', 'remote.origin.url')
    user = remote.split(':')[1].split('/')[0]
    return '%s+%s.%s' % (tags, branch, user)

if IS_LINUX or IS_MAC:
    COMPILE_ARGS = [
        '-std=c++11',
        '-ferror-limit=100',
        '-DCOMPILE_TIMESTAMP="%s"' % datetime.datetime.utcnow().isoformat(),
        '-DGIT_TAGS="%s"' % git_tags(),
        '-Wall',
        '-Wextra',
        '-Wpedantic',
        '-Wno-unused-function',
        '-Wno-extended-offsetof',
    ]
    if IS_MAC:
        COMPILE_ARGS.extend(['-mmacosx-version-min=10.9',
                             '-Wno-tautological-constant-out-of-range-compare'])
elif IS_WINDOWS:
    COMPILE_ARGS = [
        '-DNDEBUG',
        '-DWINDOWS',
        '/Dand=&&',
        '/Dnot=!',
        '/Dnot_eq=!=',
        '/Dor=||',
        '/Duint=size_t',
        # Disable warnings
        '/wd4800'
    ]


class Command(setuptools.Command):
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass


class Clean(Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        for d in CLEAN_DIRS:
            print('Deleting ./{}/'.format(d))
            shutil.rmtree(os.path.join(ROOT_DIR, d), ignore_errors=True)


class TestCpp(Command):
    description = 'Build and run C++ tests.  Might not work on windows.'

    def run(self):
        print(run('make'))
        print(run('./build/tests'))


class Generate(Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def run(self):
        print('Generate ' + ('tiny' if FLAGS.tiny else ''))

        models = FLAGS.models and re.split('[\W,]', FLAGS.models)
        generate.generate(tiny=FLAGS.tiny, models=models)


class Benchmark(Command):
    description = 'Run benchmark'

    def run(self):
        print('Benchmark')
        from benchmark.benchmark import run_benchmarks
        name = FLAGS.name
        if not name:
            parts = [FLAGS.buildtype]
            for o in FLAGS.compileropt.split():
                parts.append(o[2:])
            name = '_'.join(parts)
        run_benchmarks(FLAGS.benchmark.split(), '-'.join(parts),
                       FLAGS.benchmark_size, FLAGS.benchmark_number)


class build_ext(_build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

    def finalize_options(self):
        try:
            import Cython.Build
        except:
            print('You need to install Cython for a binary build:',
                  'http://docs.cython.org/src/quickstart/install.html')
            raise
        os.makedirs('build/genfiles/timedata', exist_ok=True)
        compile_args = COMPILE_ARGS

        if not IS_WINDOWS:
            opt_flags = BUILD_OPTIONS[FLAGS.buildtype or 'o3']
            if FLAGS.compileropt:
                opt_flags += FLAGS.compileropt.split()
            compile_args += opt_flags
            compile_args.append(
                '-DOPTIMIZATION_FLAGS="%s"' % ' '.join(sorted(opt_flags)))

        extension = setuptools.extension.Extension(
            name='timedata',
            sources=['timedata.pyx'],
            libraries=LIBRARIES,
            include_dirs=['src/cpp'],
            extra_compile_args=compile_args,
            extra_link_args=opt_flags,
            language='c++',
        )

        module = Cython.Build.cythonize(
            [extension],
            language='c++',
            language_level=3,

            compiler_directives=dict(
                c_string_encoding='ascii',
                # c_string_type='unicode', # Why doesn't this work?
            )
        )
        self.distribution.ext_modules = module
        super(build_ext, self).finalize_options()

COMMANDS = {
    'benchmark': Benchmark,
    'build_ext': build_ext,
    'clean': Clean,
    'generate': Generate,
    'test_cpp': TestCpp,
    }


# http://stackoverflow.com/a/37033551/43839
def test_suite():
    return unittest.TestLoader().discover('src/py', pattern='*_test.py')


setuptools.setup(
    name='timedata',
    packages=['src/py/timedata_tests'],
    version='0.8',
    keywords=['color', 'cython', 'dsp', 'C++'],
    description="""\
High-performance arithmetic for RGB color and for time data in general.""",
    author='Tom Swirly',
    author_email='tom@swirly.com',
    url='https://github.com/rec/timedata',
    test_suite='setup.test_suite',
    download_url='https://github.com/rec/timedata/releases/tag/v0.8',
    cmdclass=COMMANDS,
)
