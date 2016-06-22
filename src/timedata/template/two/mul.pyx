### comment

"""The mul method for list like classes."""

### declare
    void magic_$name(size_t size, $class_cpp&)

### define
    def __${name}__(object self, object other):
        # A little tricky because the $class_py can appear on the left or the
        # right side of the argument.
        cdef size_t mult
        cdef $class_py cl = $class_py()
        if isinstance(self, $class_py):
            cl.cdata = (<$class_py> self).cdata
            mult = <size_t> other
        else:
            cl.cdata = (<$class_py> other).cdata
            mult = <size_t> self
        magic_$name(mult, cl.cdata)

    def __i${name}__($class_py self, size_t mult):
        magic_$name(mult, self.cdata)
