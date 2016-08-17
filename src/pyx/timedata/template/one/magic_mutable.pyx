### define
    def ${name}_into($classname self, object x):
        """$documentation"""
        cdef $sampleclass a = x if isinstance(x, $sampleclass) else $sampleclass(x)
        self.cdata = magic_$name(self.cdata, a.cdata);
        return self
