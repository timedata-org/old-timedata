### declare
    C$classname magic_$name(C$classname&, C$classname&)

### define
    def ${name}($classname self, object x):
        """Method corresponding to magic method __${name}__ that mutates self."""
        cdef $classname a = x if isinstance(x, $classname) else self.__class__(x)
        self.cdata = magic_$name(self.cdata, a.cdata);
        return self
