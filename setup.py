#!/usr/bin/env python3

import platform, distutils.core, distutils.extension, Cython.Build

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
distutils.core.setup(name='fcolor', ext_modules=EXT_MODULES)
