cdef class _Wrapper:
    def __init__(self, **kwds):
        for k, v in kwds.items():
            if not k in self.__dict__:
                raise ValueError('Bad key ' + str(k))
            setattr(self, k, v)

    def __repr__(self):
        return '%s.%s(%s)' % (
            self.__class__.__module__,
            self.__class__.__name__[1:],
            str(self)[1:-1])
