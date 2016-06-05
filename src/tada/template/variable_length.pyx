### declare
    void {set_at}({class_cpp}, size_t, {element_cpp})
    bool {slice_into}(cl.{member}, self.{member}, begin, end, step):
    {class_cpp} = {slice_out}({class_cpp}&, int, int, int)

### define
    cdef void _set_at(self, size_t index, object x):
        return {set_at}(self.{member}, i, {element_py}(x){element_member})

    @staticmethod
    def index_error(i):
        raise IndexError('{class_py} index out of range %s' + i)

    def __init__(self, items=None):
        """Construct a {class_py} with an iterator of items, each of which looks
           like a {element_py}."""
        cdef {element_py} s
        size_t i
        if items is not None:
            if isinstance(items, {class_py}:
                self.{member} = (<{class_py}> items).{member}
            else:
                # A list of tuples, {class_py}s or strings.
                self.{member}.resize(len(items))
                for i, item in enumerate(items):
                    self._set_at(i, item)

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step, index
        cdef {class_py} cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.{member}.size())
            if isinstance(x, {class_py}:
                cl = <{class_py}> x
            else:
                cl = {class_py}(x)
            if {slice_into}(cl.{member}, self.{member}, begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        if not self._set_at(key, item):
            self.index_error(key)

    def __getitem__(self, object key):
        cdef {element_py} s
        cdef {class_py} cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.{member}.size())
            cl = {class_py}()
            cl.{member} = {slice_out}(self.{member}, begin, end, step)
            return cl

        if not self._set_at(key, item):
            self.index_error(key)
