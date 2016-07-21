### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    ctypedef vector[C$sampleclass] C$classname

    string toString(C$classname&)
    C$classname sliceOut(C$classname&, int begin, int end, int step)
    C$sampleclass max_cpp(C$classname&)
    C$sampleclass min_cpp(C$classname&)

    bool cmpToRichcmp(float cmp, int richcmp)
    $number_type compare(C$classname&, C$classname&)
    $number_type compare(C$sampleclass&, C$classname&)
    $number_type compare($number_type, C$classname&)
    bool pop(C$classname&, int key, C$sampleclass&)
    bool resolvePythonIndex(int& index, size_t size)
    bool sliceInto(C$classname&, C$classname&, int begin, int end, int step)

    int index(C$classname&, C$sampleclass&)

    size_t count(C$classname&, C$sampleclass&)

    void erase(int key, C$classname&)
    void extend(C$classname&, C$classname&)
    void insert(int key, C$sampleclass&, C$classname)
    void rotate(C$classname&, int pos)
    void rotate(C$classname&, C$classname&, int pos)
    void round_cpp(C$classname&, size_t digits)
    void round_cpp(C$classname&, C$classname&, size_t digits)
    void sliceDelete(C$classname&, int begin, int end, int step)
    void sort(C$classname&)
    void sort(C$classname&, C$classname&, bool reverse)
    void spreadAppend(C$sampleclass& end, size_t size, C$classname& out)

### define
    def __init__($classname self, items=None):
        """Construct a $classname with an iterator of items, each of which looks
           like a $sampleclass."""
        cdef $sampleclass s
        cdef size_t i
        if items is not None:
            if isinstance(items, $classname):
                self.cdata = (<$classname> items).cdata
            else:
                # A list of tuples, $classname or strings.
                self.cdata.resize(len(items))
                for i, item in enumerate(items):
                    self.cdata[i] = $sampleclass(item).cdata

    def __setitem__($classname self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step, index
        cdef $classname cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = x if isinstance(x, $classname) else $classname(x)
            if sliceInto(cl.cdata, self.cdata, begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        index = key
        if not resolvePythonIndex(index, self.cdata.size()):
            raise IndexError('$classname index out of range %s' % key)
        self.cdata[index] = $sampleclass(x).cdata

    def __getitem__($classname self, object key):
        cdef $sampleclass s
        cdef $classname cl
        cdef int k, begin, end, step
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = $classname()
            cl.cdata = sliceOut(self.cdata, begin, end, step)
            return cl
        k = key
        if not resolvePythonIndex(k, self.cdata.size()):
            raise IndexError('$classname index out of range %s' % key)
        s = $sampleclass()
        s.cdata = self.cdata[k]
        return s

    def __delitem__($classname self, object key):
        cdef int k, begin, end, step
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            sliceDelete(self.cdata, begin, end, step)
        else:
            k = key
            if not resolvePythonIndex(k, self.cdata.size()):
                raise IndexError('$classname index out of range %s' % key)
            erase(k, self.cdata)

    def __len__($classname self):
        return self.cdata.size()

    def __richcmp__(object self, object other, int rcmp):
        cdef $classname cl
        cdef bool inv = not isinstance(self, $classname)
        cdef $number_type c, mult = 1
        if not inv:
            self, other = other, self
            mult = -1
        cl = <$classname> self
        if isinstance(other, Number):
            c = compare((<$number_type> other), cl.cdata)
        elif isinstance(other, $sampleclass):
            c = compare((<$sampleclass> other).cdata, cl.cdata)
        else:
            c = compare((<$classname> other).cdata, cl.cdata)
        return cmpToRichcmp(mult * c, rcmp)

    cpdef $classname append($classname self, $sampleclass c):
        """Append to the list of samples."""
        self.cdata.push_back(c.cdata)
        return self

    cpdef size_t count(self, $sampleclass sample):
        """Return the number of times a sample appears in this list."""
        return count(self.cdata, sample.cdata)

    cpdef $classname extend($classname self, object values):
        """Extend the samples from an iterator."""
        extend($classname(values).cdata, self.cdata)
        return self

    cpdef index($classname self, $sampleclass sample):
        """Returns an index to the first occurance of that Sample, or
           raises a ValueError if that Sample isn't there."""
        cdef int id = index(self.cdata, sample.cdata)
        if id >= 0:
            return id
        raise ValueError('Can\'t find sample %s' % sample)

    cpdef $classname insert($classname self, int key,
                           $sampleclass sample):
        """Insert a sample before key."""
        insert(key, sample.cdata, self.cdata)
        return self

    cpdef $sampleclass pop($classname self, int key = -1):
        """Pop the sample at key."""
        cdef $sampleclass result = $sampleclass()
        if pop(self.cdata, key, result.cdata):
            return result
        raise IndexError('pop index out of range')

    cpdef $classname remove(self, $sampleclass sample):
        """Find and remove a specific sample."""
        self.pop(self.index(sample))
        return self

    cpdef $classname resize($classname self, size_t size):
        """Set the size of the SampleList, filling with black if needed."""
        self.cdata.resize(size)
        return self

    cpdef $classname rotate(self, int pos):
        """In-place rotation of the samples forward by `pos` positions."""
        rotate(self.cdata, pos)
        return self

    cpdef $classname rotate_to(self, int pos, $classname out):
        """In-place rotation of the samples forward by `pos` positions."""
        rotate(self.cdata, out.cdata, pos)
        return out

    def sort($classname self, object key=None, bool reverse=False):
        """Sort."""
        if key is None:
            sort(self.cdata)
            if reverse:
                self.reverse()
        else:
            # Use Python.
            self[:] = sorted(self, key=key, reverse=reverse)
        return self

    def sort_to($classname self, $classname out,
                object key=None, bool reverse=False):
        """Sort to another vector."""
        if key is None:
            sort(self.cdata, out.cdata, reverse)
        else:
            # Use Python.
            out[:] = sorted(self, key=key, reverse=reverse)
        return out

    cpdef $classname round($classname self, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, digits)
        return self

    cpdef $classname round_to($classname self, $classname out, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, out.cdata, digits)
        return out

    cpdef $sampleclass max(self):
        """Return the maximum values of each component."""
        cdef $sampleclass result = $sampleclass()
        result.cdata = max_cpp(self.cdata)
        return result

    cpdef $sampleclass min(self):
        """Return the minimum values of each component/"""
        cdef $sampleclass result = $sampleclass()
        result.cdata = min_cpp(self.cdata)
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
