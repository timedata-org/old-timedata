### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    void round_cpp(C$classname&, size_t digits)
    void round_cpp(C$classname&, C$classname&, size_t digits)
    void spreadAppend($itemclass& end, size_t size, C$classname& out)

### define
    RANGE = $range

    cpdef $classname append($classname self, object c):
        """Append to the list of samples."""
        cdef $sampleclass x = c if isinstance(c, $sampleclass) else $itemmaker(c)
        self.cdata.push_back(x$itemgetter)
        return self

    cpdef _compare($classname self, object other):
        if isinstance(other, Number):
            return compare((<$number_type> other), self.cdata)
        elif isinstance(other, $sampleclass):
            return compare((<$sampleclass> other)$itemgetter, self.cdata)
        else:
            return compare((<$classname> other).cdata, self.cdata)

    cpdef get($classname self, int key, $mutableclass previous=None):
        cdef $mutableclass result = previous if previous else $mutableclass()
        if not resolvePythonIndex(key, self.cdata.size()):
            raise IndexError('$classname index out of range %s' % key)
        result$itemgetter = self.cdata[key]
        return result

    cpdef Indexer indexer($classname self):
        """Return an RGBIndexer in Python form."""
        cpdef Indexer indexer = Indexer()
        indexer.cdata = getIndexer(self.cdata)
        return indexer

    cpdef $classname round($classname self, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        cdef $classname out = $classname()
        round_cpp(self.cdata, out.cdata, digits)
        return out

    cpdef $classname round_into($classname self, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, digits)
        return self

    cpdef $classname round_to($classname self, $classname out, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, out.cdata, digits)
        return out

    cpdef $sampleclass max(self):
        """Return the maximum values of each component."""
        cdef $sampleclass result = $emptyitem
        result$itemgetter = max_cpp(self.cdata)
        return result

    cpdef $sampleclass min(self):
        """Return the minimum values of each component."""
        cdef $sampleclass result = $emptyitem
        result$itemgetter = min_cpp(self.cdata)
        return result

    @staticmethod
    def spread(*args):
        """Spreads!"""
        cdef $classname cl = $classname()
        cdef $sampleclass sample
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                sample = $sampleclass(item)
                spreadAppend(sample.cdata, last_number - 1, cl.cdata)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        spread_append(None)
        return cl
