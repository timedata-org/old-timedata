import imp

from libc.math cimport sqrt

def square_root(double x):
    return sqrt(x)

submodule = imp.new_module('submodule')
submodule.square_root = square_root

del imp, square_root
