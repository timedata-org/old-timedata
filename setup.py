#!/usr/bin/env python3

import os, platform, distutils.core, distutils.extension, Cython.Build

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
        execute('rm -Rf ./build src/fcolor.cpp')


LIBRARIES = [] if platform.system() in ('Darwin', 'Linux') else ['m']

EXTENSION = distutils.extension.Extension(
    name='fcolor',
    sources=['src/fcolor.pyx'],
    libraries=LIBRARIES,
    include_dirs=['src'],
    extra_compile_args=['-Wno-unused-function'],
    language='c++',
    )

EXT_MODULES=Cython.Build.cythonize([EXTENSION])

distutils.core.setup(
    name='fcolor',
    cmdclass={'clean': Clean},
    ext_modules=EXT_MODULES,
    )
