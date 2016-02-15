import platform

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

libraries = ['m'] if platform.system() not in ('Darwin', 'Linux') else []

ext_modules=[
    Extension('main', sources=['main.pyx'], libraries=libraries)
]

setup(
  name = 'main',
  ext_modules = cythonize(ext_modules)
)
