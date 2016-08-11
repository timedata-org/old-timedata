class Context(object):
    def __init__(self, **kwds):
        for (k, v) in kwds.items():
            setattr(self, k, v)
