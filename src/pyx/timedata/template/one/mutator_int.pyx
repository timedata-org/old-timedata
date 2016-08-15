### define
    cpdef $classname ${name}_into($classname self, int index):
        """$documentation"""
        self.cdata = $name(self.cdata, index)
        return self
