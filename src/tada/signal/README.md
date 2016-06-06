# Musings #

We have Models that are generic on:

* Name - an enumerated type with names of the fields in the model (e.g. red, green, blue).
* Range - Generic Numbers (min, range)

For each Model we expose as Python

Model::Data
Model::Vector



The model especific parts are as follows:

* Conversion to or from a named string.
* There needs to a whole section for "conversions between types"


My original notes:


Classes of methods:

-- hardcoded!
* two string magic functions with no arguments
    def __repr__({class_py} self):
    def __str__({class_py} self):

everything above this line, plus some others, gets hardcoded into the
template as it's exactly the same for everyone.


--- this next section has all the same TEMPLATE --
* seven arithmetic magic functions with no arguments
    def __abs__({class_py} self):
    def __ceil__({class_py} self):
    def __floor__({class_py} self):
    def __hash__({class_py} self):
    def __invert__({class_py} self):
    def __neg__({class_py} self):
    def __trunc__({class_py} self):

* one method with no arguments
    cpdef normalized({class_py} self):  # probably to be deleted.

* one model-specific method
    cpdef to_hex({class_py} self):

-- done --


-- these magic functions have the same TEMPLATE. --
* six arithmetic magic functions with one argument of the same type.
    def __add__(self, c):
    def __divmod__(self, c):
    def __mod__(self, c):
    def __mul__(self, c):
    def __sub__(self, c):
    def __truediv__(self, c):

-- special case
* one arithmetic magic function with an optional int argument
    def __round__({class_py} self, int n = 0):

-- special case
# one arithmetic magic function with two arguments.
    def __pow__(self, c, mod):

-- special case
# one comparison magic function with two arguments
    def __richcmp__({class_py} self, {class_py} c, int cmpType):

-- general for all classes.
# one generic static method.
    @staticmethod
    def names():

-- these have the same template --
* three methods with one argument of same type that return a float.
  * distance
  * distance2
  * dot (not written)

* two methods with one argument of same type that return a sample
  * max_limit
  * min_limit

-- done --

* one method with an int argument
    cpdef rotated({class_py} self, int positions):

* one model-specific @staticmethod
    def from_hex(uint32_t hex):

* total 28 methods.
"""
