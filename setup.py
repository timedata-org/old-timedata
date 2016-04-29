#!/usr/bin/env python3

import platform

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

libraries = [] if platform.system() in ('Darwin', 'Linux') else ['m']

ext_modules=[
    Extension('main', sources=['src/main.pyx'], libraries=libraries)
]

setup(
  name = 'main',
  ext_modules = cythonize(ext_modules)
)
