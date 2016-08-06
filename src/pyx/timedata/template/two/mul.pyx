### comment

"""The mul method for list like classes."""

### declare
    void magic_$name(size_t size, C$classname&)

### define
    def __${name}__(object self, object other):
        """$documentation that returns a new $classname."""
        # A little tricky because the $classname can appear on the left or the
        # right side of the argument.
        cdef size_t mult
        cdef $classname cl = $classname()
        if isinstance(self, $classname):
            cl.cdata = (<$classname> self).cdata
            mult = <size_t> other
        else:
            cl.cdata = (<$classname> other).cdata
            mult = <size_t> self
        magic_$name(mult, cl.cdata)
        return cl

    def __i${name}__($classname self, size_t mult):
        """$documentation that writes into self."""
        magic_$name(mult, self.cdata)
        return self
