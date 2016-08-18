### define
    cpdef _compare($classname self, object other):
        if isinstance(other, Number):
            return compare((<$number_type> other), self.cdata)
        return compare((<$classname> other).cdata, self.cdata)

    cpdef $classname append($classname self, size_t c):
        """Append to the list of samples."""
        self.cdata.push_back(c)
        return self
