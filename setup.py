#!/usr/bin/env python3

"""This is the main builder and installer for the Templated Digital Signal
Processing Python extension."""

import datetime, glob, os, platform, shutil
import distutils.core, distutils.extension, Cython.Build

import Cython.Compiler.Options

# Uncomment this next line if you want Cython to output HTML showing how C++-ey
# it can make your code.
# Same as --annotate here: http://docs.cython.org/src/quickstart/cythonize.html
#
# Cython.Compiler.Options.annotate = True

IS_MAC = (platform.system() == 'Darwin')
IS_LINUX = (platform.system() == 'Linux')
IS_DEBIAN = IS_LINUX and (platform.linux_distribution()[0] == 'debian')

LIBRARIES = [] if (IS_MAC or IS_LINUX) else ['m']

COMPILE_ARGS = [
    '-O3',
    '-DNDEBUG',
    '-DCOMPILE_TIMESTAMP="%s"' % datetime.datetime.utcnow().isoformat(),
    '-Wno-unused-function',
    '-std=c++11',
    ]

if IS_MAC:
    COMPILE_ARGS.extend(['-mmacosx-version-min=10.9',
                         '-Wno-tautological-constant-out-of-range-compare'])

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
        execute('rm -Rf ./build src/tada.cpp')


class Local(distutils.core.Command):
    description = 'Install the .so locally'
    user_options = []

    # TODO: need to get this from distutils somehow.

    TARGET_LOCATIONS = 'tada', '/development/BiblioPixel'
    # TODO: awful hack.

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        files = glob.glob('build/lib*/*.so')
        assert len(files) == 1, files
        
        for target in self.TARGET_LOCATIONS:
            try:
                os.remove(target)
            except:
                pass
            shutil.copy2(files[0], os.path.join(target, 'tada.so'))


EXTENSION = distutils.extension.Extension(
    name='tada',
    sources=['src/tada.pyx'],
    libraries=LIBRARIES,
    include_dirs=['src'],
    extra_compile_args=COMPILE_ARGS,
    language='c++',
    )

EXT_MODULES=Cython.Build.cythonize(
    [EXTENSION],
    language='c++',
    language_level=3,

    compiler_directives=dict(
        c_string_encoding='ascii',
        # c_string_type='unicode', # Why doesn't this work?
        )
    )

distutils.core.setup(
    name='tada',
    cmdclass={'clean': Clean, 'local': Local},
    ext_modules=EXT_MODULES,
    )
