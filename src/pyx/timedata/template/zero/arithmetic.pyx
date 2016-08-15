### define
    cpdef $classname ${name}($classname self):
        """Python magic method __${name}__"""
        self.cdata = magic_$name(self.cdata)
        return self
