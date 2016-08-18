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
        # TODO: having these different map/remap is sketchy.  Rethink!
        if len(result) < len(self):
            result.resize(len(self))
        for i in range(len(self)):
            index = self.cdata[i]
            if index < <size_t> len(x):
                result[i] = x[index]
            # TODO: else what?
        return result

    cpdef object map($classname self, object x):
        return self.map_to(x, x.__class__())
