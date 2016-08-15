### define
    def __i${name}__($classname self, object x):
        """Python magic method __i${name}__ that mutates self."""
        cdef $classname a = x if isinstance(x, $sampleclass) else self.__class__(x)
        self.cdata = magic_$name(self.cdata, a.cdata);
        return self
