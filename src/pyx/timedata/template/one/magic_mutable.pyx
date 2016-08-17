### define
    def __i${name}__($classname self, object x):
        """Python magic method __i${name}__ that mutates self."""
        return self.${name}_into()

    def ${name}_into($classname self, object x):
        """$documentation"""
        cdef $sampleclass a = x if isinstance(x, $sampleclass) else $sampleclass(x)
        self.cdata = magic_$name(self.cdata, a.cdata);
        return self
