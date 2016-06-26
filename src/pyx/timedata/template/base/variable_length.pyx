### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare

cdef extern from "<$include_file>" namespace "$namespace":
    cdef cppclass C$classname:
         C$classname()
         C$sampleclass& operator[](size_t)
         void fill(C$sampleclass)
         size_t size()
         void push_back(C$sampleclass)
         void resize(size_t)

    bool fixKey(int& index, size_t size)
    size_t count(C$classname&, C$sampleclass&)
    void extend(C$classname&, C$classname&)
    int index(C$classname&, C$sampleclass&)
    void insert(int key, C$sampleclass&, C$classname)
    bool pop(C$classname&, int key, C$sampleclass&)
    void rotate(C$classname&, int pos)
    void sort(C$classname&)
    void round_cpp(C$classname&, size_t digits)
    C$sampleclass max_cpp(C$classname&)
    C$sampleclass min_cpp(C$classname&)
    void spreadAppend(C$classname&, size_t, C$sampleclass&)
    bool sliceInto(C$classname&, C$classname&, int, int, int)
    C$classname sliceOut(C$classname&, int, int, int)

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
        if not fixKey(index, self.cdata.size()):
            raise IndexError('$classname index out of range %s' + key)
        self.cdata[index] = $sampleclass(x).cdata

    def __getitem__(self, object key):
        cdef $sampleclass s
        cdef $classname cl
        cdef int k, begin, end, step
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = $classname()
            cl.cdata = sliceOut(self.cdata, begin, end, step)
            return cl
        k = key
        if not fixKey(k, self.cdata.size()):
            raise IndexError('$classname index out of range %s' + key)
        s = $sampleclass()
        s.cdata = self.cdata[k]
        return s

    def __len__(self):
        return self.cdata.size()

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

    cpdef $classname round(self, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, digits)
        return self

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
                spreadAppend(cl.cdata, last_number - 1, sample.cdata)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        spread_append(None)
        return cl
