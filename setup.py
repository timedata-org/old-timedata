#!/usr/bin/env python3

"""This is the main builder and installer for the Templated Digital Signal
Processing Python extension."""

import datetime, glob, os, platform, shutil, subprocess, sys, unittest
import setuptools.extension
from setuptools.command.build_ext import build_ext as _build_ext

sys.path.append('src/py')
from timedata_build import generate

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
    def initialize_options(self):
        pass

    def finalize_options(self):
        pass


class Clean(Command):
    description = 'Complete clean command'
    user_options = []

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        for d in CLEAN_DIRS:
            print('Deleting ./{}/'.format(d))
            shutil.rmtree(os.path.join(ROOT_DIR, d), ignore_errors=True)


class Generate(Command):
    description = 'Make generated classes'
    user_options = [['tiny=', None, 'Make a tiny build.']]

    def initialize_options(self):
        self.tiny = False

    def run(self):
        print('Generate ' + ('tiny' if self.tiny else ''))
        generate.generate(tiny=self.tiny)


class build_ext(_build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

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
    -funroll-loops"""

    user_options2 = _build_ext.user_options + [
        ['buildtype=', None, 'Select build type from o3 (default), o2, debug'],
        ['compileropt=', None, 'Additional options to the compiler.'],
        ]

    def initialize_options2(self):
        super().initialize_options()
        self.buildtype_x = self.compileropt_x = None

    def finalize_options(self):
        self.buildtype_x = self.compileropt_x = None
        try:
            import Cython.Build
        except:
            print('You need to install Cython for a binary build:',
                  'http://docs.cython.org/src/quickstart/install.html')
            raise
        os.makedirs('build/genfiles/timedata', exist_ok=True)
        compile_args = COMPILE_ARGS

        if not IS_WINDOWS:
            opt_flags = self.BUILD_OPTIONS[self.buildtype_x or 'o3']
            if self.compileropt_x:
                opt_flags += self.compileropt_x.split()
            compile_args += opt_flags
            compile_args.append(
                '-DOPTIMIZATION_FLAGS="%s"' % ' '.join(sorted(opt_flags)))

        extension = setuptools.extension.Extension(
            name='timedata',
            sources=['timedata.pyx'],
            libraries=LIBRARIES,
            include_dirs=['src/cpp'],
            extra_compile_args=compile_args,
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
    cmdclass={
        'build_ext': build_ext,
        'clean': Clean,
        'generate': Generate,
    },
)
