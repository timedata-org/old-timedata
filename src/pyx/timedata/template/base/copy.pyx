### define
    cpdef $classname copy($classname self):
        """Return a new copy of self."""
        cdef $classname s = self.__class__()
        s.cdata = self.cdata
        return s

    def __copy__($classname self):
      return self.copy()

    def __deepcopy__($classname self, memodict=None):
        return self.copy()
