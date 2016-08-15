### define
    cpdef $classname ${name}($classname self):
        """Arithmetic operation corresponding to python magic method
        __${name}__.
        """
        self.cdata = magic_$name(self.cdata)
        return self
