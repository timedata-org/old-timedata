### comment
"""Basic methods for classes of a fixed length (like a Sample)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    cdef cppclass C$classname:
         C$classname()
         C$classname($value_type, $value_type, $value_type)
         $value_type& operator[](size_t)
         void fill($value_type)

    bool fromString(string&, C$classname&)
    bool fixKey(int& index, size_t size)

### define
    def __init__(self, *args):
        """There are various different ways to construct a $classname.

        * The empty constructor $classname() set all components to zero.
        * ${classname}s can be constructed from string names.
        * Constructing from a single number results in all components
          having that value.
        * Constructing from any iteratable the right size works
          as expected.
        * Constructing from things that aren't iterable or have the wrong size
          throws the correct Python exception.
        """
        if len(args) == 1:
            a = args[0]
            if isinstance(a, Number):
                self.cdata.fill(<$value_type> a)
                return
            if isinstance(a, str):
                if fromString(<string> a, self.cdata):
                    return
                raise ValueError("Can't understand sample string %s" % args)
            try:
                args = tuple(a)
            except:
                raise ValueError("Can't understand sample tuple %s" % args)

        if not args:
            self.cdata.fill(0)
        elif len(args) != $size:
            raise ValueError("Wrong args length %s" % args)
        else:
            for i, a in enumerate(args):
                self.cdata[i] = a

    def __getitem__($classname self, object key):
        cdef int index
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return $classname(*r) if len(r) == $size else r

        index = <int> key
        if fixKey(index, $size):
            return self.cdata[index]
        raise IndexError('$classname index out of range')

    def __len__($classname self):
        return $size
