### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    void round_cpp(C$classname&, size_t digits)
    void round_cpp(C$classname&, C$classname&, size_t digits)
    void spreadAppend($itemclass& end, size_t size, C$classname& out)

### define
    RANGE = $range

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
