### comment
"""Basic methods for classes with a variable length (like a List)."""

### declare
    void $set_at($class_cpp, size_t, $element_cpp)
    bool $slice_into(cl.cdata, self.cdata, begin, end, step):
    $class_cpp = $slice_out($class_cpp&, int, int, int)

### define
    cdef void _set_at(self, size_t index, object x):
        return $set_at(self.cdata, i, $element_py(x)$element_member)

    @staticmethod
    def index_error(i):
        raise IndexError('$class_py index out of range %s' + i)

    def __init__($class_py self, items=None):
        """Construct a $class_py with an iterator of items, each of which looks
           like a $element_py."""
        cdef $element_py s
        size_t i
        if items is not None:
            if isinstance(items, $class_py:
                self.cdata = (<$class_py> items).cdata
            else:
                # A list of tuples, $class_pys or strings.
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
        if not self._set_at(key, item):
            self.index_error(key)

    def __getitem__(self, object key):
        cdef $element_py s
        cdef $class_py cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.cdata.size())
            cl = $class_py()
            cl.cdata = $slice_out(self.cdata, begin, end, step)
            return cl

        if not self._set_at(key, item):
            self.index_error(key)

    def __len__(self):
        return self.cdata.size()
