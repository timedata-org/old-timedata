import numbers

"""
Uses the following template symbols

global:

    {{begin}}
    {{class_cpp}}:
    {{class_py}}:
    {{declarations}}
    {{from_string}}:
    {{member}}
    {{range}}
    {{size}}
    {{to_string}}:

in definitions:

    {{define}}
    {{function_cpp}}
    {{function_py}}
    {{param_type}}
    {{propname}}
    {{return_type}}

"""

{declarations}

cdef class {class_py}:
    """A Sample is an immutable ranged numeric sample with named components!

       A Sample looks very much like a Python tuple with floating point
       numbers, with the big exception that operators like + and * perform
       arithmetic, not list-style operations.

       The constructor for Sample takes a tuple of numbers but also possibly
       strings representing human-readable sample names for specific samples
       called Colors.

       Sample supports the operations +, -, *, /, %, pow, and ~ (which means
       "take the complementary sample").

    """
    cdef {class_cpp} {member}

    def __init__(self, *args):
        """There are various different ways to construct a Sample.

        * The empty constructor Sample() gives all components are zero.
        * Samples can be constructed from string names.
        * Constructing from a single number results in a sample with all
          components of that value.
        * Constructing from any sort of tuple of the right size works
          as expected.
        """
        if len(args) == 1:
            a = args[0]
            if isinstance(a, numbers.Number):
                self.{member}.fill(a)
                return
            if isinstance(a, str):
                if {from_string}(a, self.{member}):
                    return
                raise ValueError("Can't understand sample string %s" % args)
            try:
                args = tuple(a)
            except:
                raise ValueError("Can't understand sample tuple %s" % args)

        if not args:
            self.{member}.fill(0)
        elif len(args) != {size}:
            raise ValueError("Wrong args length %s" % args)
        else:
            for i, a in enumerate(args):
                sample[i] = a

    def __getitem__({class_py} self, object key):
        cdef int index
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return {class_py}(*r) if len(r) == {size} else r

        index = <int> key
        if normalizeIndex(index)
            return self.{member}[index]
        raise IndexError('Sample index out of range')

    def __len__({class_py} self):
        return {size}

    def __repr__({class_py} self):
        return '{class_py}(%s)' % str(self)

    def __str__({class_py} self):
        return {to_string}(self.{member}).decode('ascii')

    @property
    def begin({class_py} self):
        """Return the lowest in-band value for this sample."""
        return {begin}

    @property
    def range({class_py} self):
        """Return the range from begin() to the highest in-band value."""
        return {range}

    cpdef {class_py} copy({class_py} self):
        cdef {class_py} s = {class_py}()
        s.{member} = self.{member}
        return s

    ### property define
    @property
    def {propname)(self):
        return self.{member}[{index}]

    ### zero_argument declare
    {class_cpp} {function_cpp}({class_py}&)

    ### zero_argument define
    {define} {function_py}({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.{member} = {function_cpp}(self.{member})
        return

    ### one_argument declare
    {return_type} {function_cpp}({class_py}&, {class_py}&)

    ### one_argument define
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        return {function_cpp}(self.{member}, s.{member})

    ### one_argument_return_sample declare
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

    ### one_argument_return_sample define
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s, result = {class_py}()
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        result.{member} = {function_cpp}(self.{member}, s.{member})
        return result

    ### magic_method declare
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

    ### magic_method define
    def {function_py}(self, object x):
        """{documentation}"""
        cdef {class_py} a, b, result = {class_py}()
        # Remember that this method will be triggered if either `self` or `x`
        # are instances of {class_py}, so we need to check the type of both.
        if isinstance(self, {class_py}):
            a = <{class_py}> self
        else:
            a = {class_py}(self)
        if isinstance(x, {class_py}):
            b = <{class_py}> x
        else:
            b = {class_py}(x)
        result.{member} = {function_cpp}(a.{member}, b.{member})
        return result

    ### static_strings declare
    vector[string] {function_cpp}()

    ### static_strings define
    @staticmethod
    def {function_py}():
        """{documentation}"""
        cdef vector[string] names
        result = []
        names = {function_cpp}()
        for i in names:
            result.append(i.decode('ascii'))
        return result

    ### static_maker declare
    {class_cpp} {function_cpp}({param_type})

    ### static_maker define
    @staticmethod
    def {function_py}({param_type} x):
        """{documentation}"""
        cdef {class_py} result = {class_py}()
        result.{member} = {function_cpp)(x)
        return result

    """

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
