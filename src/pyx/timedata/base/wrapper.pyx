cdef class _Wrapper:
    def __init__(self, **kwds):
        for k, v in kwds.items():
            setattr(self, k, v)

    def __repr__(self):
        name = self.__class__.__name__
        if name.startswith('_'):
            name = name[1:]
        return '%s.%s(%s)' % (self.__class__.__module__, name, str(self)[1:-1])
