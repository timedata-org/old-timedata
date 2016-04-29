#!/usr/bin/env python3

import platform, distutils.core, distutils.extension, Cython.Build

LIBRARIES = [] if platform.system() in ('Darwin', 'Linux') else ['m']

EXTENSION = distutils.extension.Extension(
    'main', sources=['src/main.pyx'], libraries=LIBRARIES)

EXT_MODULES=Cython.Build.cythonize([EXTENSION])

distutils.core.setup(name='main', ext_modules=EXT_MODULES)
