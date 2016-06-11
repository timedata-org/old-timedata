import os, split_parts, string

def add(*names, **kwds):
    filename = os.path.join(*names) + '.pyx'
    try:
        parts = split_parts.split(open(filename), filename)
        def _sub(name):
            return string.Template(parts.get(name, '')).substitute(**kwds)
        return _sub('declare'), _sub('define')

    except Exception as e:
        s = ' '.join(str(i) for i in e.args)
        raise e.__class__('%s in file %s' % (s, filename))
