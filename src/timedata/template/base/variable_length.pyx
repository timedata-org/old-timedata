### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare
cdef extern from "<$include_file>" namespace "$namespace":
    cdef cppclass $class_cpp:
         $class_cpp()
         $sample_cpp& operator[](size_t)
         void fill($sample_cpp)
         size_t size()
         void push_back($sample_cpp)
         void resize(size_t)

    bool $from_string(string&, $class_cpp&)
    bool $fix_key(int& index, size_t size)

    void append($class_cpp, $sample_cpp&)
    size_t count($class_cpp&, $sample_cpp&)
    void extend($class_cpp&, $class_cpp&)
    int index($class_cpp&, $sample_cpp&)
    void insert(int key, $sample_cpp&, $class_cpp)
    bool pop($class_cpp&, int key, $sample_cpp&)
    void rotate($class_cpp&, int pos)
    void sort($class_cpp&)
    void round_cpp($class_cpp&, size_t digits)
    $sample_cpp max_cpp($class_cpp&)
    $sample_cpp min_cpp($class_cpp&)
    void spreadAppend($class_cpp&, size_t, $sample_cpp&)
    bool $set_at($class_cpp&, size_t, $sample_cpp)
    bool $slice_into($class_cpp&, $class_cpp&, begin, end, step)
    $class_cpp $slice_out($class_cpp&, int, int, int)

### define
    cdef bool _set_at(self, size_t i, object x):
        return $set_at(self.cdata, i, $sample_py(x).cdata)

    @staticmethod
    def index_error(i):
        raise IndexError('$class_py index out of range %s' + i)

    def __init__($class_py self, items=None):
        """Construct a $class_py with an iterator of items, each of which looks
           like a $sample_py."""
        cdef $sample_py s
        cdef size_t i
        if items is not None:
            if isinstance(items, $class_py):
                self.cdata = (<$class_py> items).cdata
            else:
                # A list of tuples, $class_py or strings.
                self.cdata.resize(len(items))
                for i, item in enumerate(items):
                    self._set_at(i, item)

    def __setitem__($class_py self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step, index
        cdef $class_py cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = x if isinstance(x, $class_py) else $class_py(x)
            if $slice_into(cl.cdata, self.cdata, begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        if not self._set_at(key, x):
            self.index_error(key)

    def __getitem__(self, object key):
        cdef $sample_py s
        cdef $class_py cl
        cdef int k, begin, end, step
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = $class_py()
            cl.cdata = $slice_out(self.cdata, begin, end, step)
            return cl
        k = key
        if not $fix_key(k, self.cdata.size()):
            self.index_error(key)
        s = $sample_py()
        s.cdata = self.cdata[k]
        return s

    def __len__(self):
        return self.cdata.size()

    cpdef $class_py append($class_py self, $sample_py c):
        """Append to the list of samples."""
        self.cdata.push_back(c.cdata)
        return self

    cpdef size_t count(self, $sample_py sample):
        """Return the number of times a sample appears in this list."""
        return count(self.cdata, sample.cdata)

    cpdef $class_py extend($class_py self, object values):
        """Extend the samples from an iterator."""
        extend($class_py(values).cdata, self.cdata)
        return self

    cpdef index($class_py self, $sample_py sample):
        """Returns an index to the first occurance of that Sample, or
           raises a ValueError if that Sample isn't there."""
        cdef int id = index(self.cdata, sample.cdata)
        if id >= 0:
            return id
        raise ValueError('Can\'t find sample %s' % sample)

    cpdef $class_py insert($class_py self, int key,
                           $sample_py sample):
        """Insert a sample before key."""
        insert(key, sample.cdata, self.cdata)
        return self

    cpdef $sample_py pop($class_py self, int key = -1):
        """Pop the sample at key."""
        cdef $sample_py result = $sample_py()
        if pop(self.cdata, key, result.cdata):
            return result
        raise IndexError('pop index out of range')

    cpdef $class_py remove(self, $sample_py sample):
        """Find and remove a specific sample."""
        self.pop(self.index(sample))
        return self

    cpdef $class_py resize($class_py self, size_t size):
        """Set the size of the SampleList, filling with black if needed."""
        self.cdata.resize(size)
        return self

    cpdef $class_py rotate(self, int pos):
        """In-place rotation of the samples forward by `pos` positions."""
        rotate(self.cdata, pos)
        return self

    def sort($class_py self, object key=None, bool reverse=False):
        """Sort."""
        if key is None:
            sort(self.cdata)
            if reverse:
                self.reverse()
        else:
            # Use Python.
            self[:] = sorted(self, key=key, reverse=reverse)
        return self

    cpdef $class_py round(self, uint digits=0):
        """Round each element in each sample to the nearest integer."""
        round_cpp(self.cdata, digits)
        return self

    cpdef $sample_py max(self):
        """Return the maximum values of each component."""
        cdef $sample_py result = $sample_py()
        result.cdata = max_cpp(self.cdata)
        return result

    cpdef $sample_py min(self):
        """Return the minimum values of each component/"""
        cdef $sample_py result = $sample_py()
        result.cdata = min_cpp(self.cdata)
        return result

    @staticmethod
    def spread(*args):
        """Spreads!"""
        cdef $class_py cl = $class_py()
        cdef $sample_py sample
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                sample = $sample_py(item)
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
