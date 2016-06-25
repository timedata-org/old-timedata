cdef class _Wrapper:
    def __init__(self, **kwds):
        d = getattr(self, '__dict__', {})
        for k, v in kwds.items():
            setattr(self, k, v)

    def __repr__(self):
        return '%s.%s(%s)' % (
            self.__class__.__module__,
            self.__class__.__name__[1:],
            str(self)[1:-1])
