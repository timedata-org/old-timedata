### comment
"""Basic methods for classes of a fixed length (like a Sample)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    cdef cppclass C$classname:
         C$classname()
         C$classname($number_type, $number_type, $number_type)
         $number_type& operator[](size_t)
         void fill($number_type)

    bool compare(C$classname&, C$classname&, int richcmp)
    bool fromString(string&, C$classname&)
    bool resolvePythonIndex(int& index, size_t size)

### define
    MODEL = className[C$classname]()

    def __init__($classname self, *args):
        """A $classname can be constructed as follows:

        * The empty constructor $classname() sets each component to zero.

        * ${classname}s can be constructed intuitively from string names.
          Details TBD.

        * Constructing from a $number_type sets each component to that
          value.

        * Constructing from an iteratable of size $size sets each
          component from the iterable.

        * Constructing from $size ${value_type}s sets the corresponding
          components.

        * Anything else throws an exception.
"""
        cdef string model
        cdef uint64_t pointer
        while len(args) == 1:
            a = args[0]
            if isinstance(a, Number):
                self.cdata.fill(<$number_type> a)
                return
            if isinstance(a, str):
                if fromString(<string> a, self.cdata):
                    return
                raise ValueError("Can't understand sample string %s" % args)
            if isinstance(a, $classname):
                self.cdata = (<$classname> a).cdata
                return
            m = getattr(a, 'MODEL', None)
            if m:
                model = m
                pointer = a._get_pointer()
                # error = getModel[C$classname].convert(self.cdata, pointer, model)
                error = '' # getModel[C$classname].name()
                if not error:
                    return
                raise ValueError("Can't convert from model %s, value %s" %
                                 (model, a))

            try:
                args = tuple(a)
            except:
                raise ValueError("Can't understand sample tuple %s" % args)

        if not args:
            self.cdata.fill(0)
        elif len(args) != $size:
            raise ValueError("Wrong args length %s, should be $size" % args)
        else:
            for i, a in enumerate(args):
                self.cdata[i] = a

    cpdef uint64_t _get_pointer($classname self):
        return referenceToInteger(self.cdata)

    def __getitem__($classname self, object key):
        cdef int index
        if not isinstance(key, slice):
            index = <int> key
            if resolvePythonIndex(index, $size):
                return self.cdata[index]
            raise IndexError('$classname index out of range')

        # Use Python to actually do the slicing.
        t = tuple(self[i] for i in range(*key.indices($size)))

        # Try to remain as $classname if possible.
        return $classname(*t) if len(t) == $size else t

    def __len__($classname self):
        return $size

    def __richcmp__($classname self, $classname other, int rcmp):
        return compare(self.cdata, other.cdata, rcmp)
