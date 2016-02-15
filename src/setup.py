from distutils.core import setup
from Cython.Build import cythonize

setup(
  name = 'fcolor app',
  ext_modules = cythonize('main.pyx'),
)
