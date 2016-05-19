#!/usr/bin/env python3

import datetime, os, platform, shutil
import distutils.core, distutils.extension, Cython.Build

import Cython.Compiler.Options

Cython.Compiler.Options.annotate = True

def execute(command):
    result = os.system(command)
    if result:
        raise Exception('%s\n failed with code %s' % (command, result))


class Clean(distutils.core.Command):
    description = 'Complete clean command'
    user_options = []

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        assert os.getcwd() == self.cwd, 'Must be in package root: %s' % self.cwd
        execute('rm -Rf ./build src/tdsp.cpp')


class Local(distutils.core.Command):
    description = 'Install the .so locally'
    user_options = []

    FILE_LOCATION = 'build/lib.macosx-10.6-intel-3.4/tdsp.so'
    # TODO: need to get this from distutils somehow.

    TARGET_LOCATIONS = 'tdsp', '/development/BiblioPixel'
    # TODO: awful hack.

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        for target in self.TARGET_LOCATIONS:
            try:
                os.remove(target)
            except:
                pass
            shutil.copy2(self.FILE_LOCATION, target)


LIBRARIES = [] if platform.system() in ('Darwin', 'Linux') else ['m']

COMPILE_ARGS = [
    '-O3',
    '-DNDEBUG',
    '-DCOMPILE_TIMESTAMP="%s"' % datetime.datetime.utcnow().isoformat(),
    '-Wno-unused-function',
    '-std=c++11',
    '-Wno-tautological-constant-out-of-range-compare',
#    '--version',
    ]

if platform.system() == 'Darwin':
    COMPILE_ARGS.append('-mmacosx-version-min=10.9')


EXTENSION = distutils.extension.Extension(
    name='tdsp',
    sources=['src/tdsp.pyx'],
    libraries=LIBRARIES,
    include_dirs=['src'],
    extra_compile_args=COMPILE_ARGS,
    language='c++',
    )

EXT_MODULES=Cython.Build.cythonize(
    [EXTENSION],
    language='c++',
    language_level=3,
    annotate=True,

    compiler_directives=dict(
        annotate=True,
        c_string_encoding='ascii',
        # c_string_type='unicode', # Why doesn't this work?
        )
    )

distutils.core.setup(
    name='tdsp',
    cmdclass={'clean': Clean, 'local': Local},
    ext_modules=EXT_MODULES,
    )
