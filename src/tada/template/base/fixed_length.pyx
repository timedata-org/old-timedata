### comment
"""Basic methods for classes of a fixed length (like a Sample)."""

### declare
    bool $from_string(string&, $class_cpp&)
    bool $fix_key(int& index, size_t size)

### define
    def __init__(self, *args):
        """There are various different ways to construct a $class_py.

        * The empty constructor $class_py() set all components to zero.
        * ${class_py}s can be constructed from string names.
        * Constructing from a single number results in all components
          having that value.
        * Constructing from any iteratable the right size works
          as expected.
        * Constructing from things that aren't iterable or have the wrong size
          throws the correct Python exception.
        """
        cdef ${value_type} number
        if len(args) == 1:
            a = args[0]
            if isinstance(a, Number):
                number = a
                self.cdata.fill(number)
                return
            if isinstance(a, str):
                if $from_string(a, self.cdata):
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

    def __getitem__($class_py self, object key):
        cdef int index
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return $class_py(*r) if len(r) == $size else r

        index = <int> key
        if $fix_key(index, $size):
            return self.cdata[index]
        raise IndexError('$class_py index out of range')

    def __len__($class_py self):
        return $size
