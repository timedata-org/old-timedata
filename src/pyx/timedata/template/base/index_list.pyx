### define
    cpdef _compare($classname self, object other):
        if isinstance(other, Number):
            return compare((<$number_type> other), self.cdata)
        return compare((<$classname> other).cdata, self.cdata)

    cpdef $classname append($classname self, size_t c):
        """Append to the list of samples."""
        self.cdata.push_back(c)
        return self

    cpdef object map_to($classname self, object x, object result):
        cdef int index
        if len(result) < len(self):
            result.resize(len(self))
        for i in range(len(self)):
            index = self.cdata[i]
            if not resolvePythonIndex(index, len(x)):
                raise IndexError('Bad index %s' % index)
            result[i] = x[index]
        return result

    cpdef object map($classname self, object x):
        return self.map_to(x, x.__class__())

    def __getstate__(self):
        return tuple(i for i in self.cdata)

    def __setstate__(self, state):
        self.cdata.resize(len(state))
        for i, s in enumerate(state):
            self.cdata[i] = state[i]
