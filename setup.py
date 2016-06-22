#!/usr/bin/env python3

"""This is the main builder and installer for the Templated Digital Signal
Processing Python extension."""

import datetime, generate, glob, os, platform, shutil, subprocess, unittest
import setuptools.extension, Cython.Build
from setuptools.command.build_ext import build_ext as _build_ext

import Cython.Compiler.Options

# Uncomment this next line if you want Cython to output HTML showing how C++-ey
# it can make your code.
# Same as --annotate here: http://docs.cython.org/src/quickstart/cythonize.html
#
# Cython.Compiler.Options.annotate = True

IS_MAC = (platform.system() == 'Darwin')
IS_LINUX = (platform.system() == 'Linux')
IS_DEBIAN = IS_LINUX and (platform.linux_distribution()[0] == 'debian')
IS_WINDOWS = (platform.system() == 'Windows')

LIBRARIES = [] if (IS_MAC or IS_LINUX or IS_WINDOWS) else ['m']

ROOT_DIR = os.path.dirname(os.path.realpath(__file__))

CLEAN_DIRS = ['build']
CLEAN_FILES = ['src/timedata.cpp']


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
        '-O3',
        '-DNDEBUG',
        '-DCOMPILE_TIMESTAMP="%s"' % datetime.datetime.utcnow().isoformat(),
        '-DGIT_TAGS="%s"' % git_tags(),
        '-Wall',
        '-Wextra',
        '-Wpedantic',
        '-std=c++11',
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
        for f in CLEAN_FILES:
            print('Deleting ./{}'.format(f))
            try:
                os.remove(os.path.join(ROOT_DIR, f))
            except OSError:
                pass


class Generate(Command):
    description = 'Make generated classes'
    user_options = []

    def run(self):
        print('Run Generate')
        generate.generate()


class Local(Command):
    description = 'Install the binary locally'
    user_options = []

    # TODO: need to get this from setuptools somehow.

    TARGET_LOCATIONS = 'timedata', '/development/BiblioPixel'
    # TODO: awful hack.

    def run(self):
        print('Run Local')
        files = glob.glob('build/lib*/*.so') + glob.glob('build/lib*/*.pyd')
        assert len(files) == 1, files

        binfile = files[0]
        _, ext = os.path.splitext(binfile)
        for target in self.TARGET_LOCATIONS:
            try:
                os.remove(target)
            except:
                pass
            shutil.copy2(binfile, os.path.join(target, 'timedata' + ext))


class build_ext(_build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

    def finalize_options(self):
        extension = setuptools.extension.Extension(
            name='timedata',
            sources=['src/timedata.pyx'],
            libraries=LIBRARIES,
            include_dirs=['src'],
            extra_compile_args=COMPILE_ARGS,
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
    return unittest.TestLoader().discover('timedata', pattern='*_test.py')

setuptools.setup(
    name='timedata',
    packages=['timedata_tests'],
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
