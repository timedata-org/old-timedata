class Context(object):
    def __init__(self, *items, **kwds):
        def run(x):
            for k, v in x.items():
                setattr(self, k, v)
        for i in items:
            run(i.__dict__)
        run(kwds)


def public_dir(x):
    return {k: v for (k, v) in x.__dict__.items() if not k.startswith('_')}
