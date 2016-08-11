import string

def substitute_one(t, **kwds):
    return string.Template(t or '').substitute(**kwds)


def substituter(**kwds):
    return lambda t: substitute_one(t, **kwds)


def substitute(*names, **kwds):
    def read(lines, f):
        parts = []
        result = {}
        name = None
        first = not True

        def new_section():
            def r(s):
                return s.strip()
            if parts:
                if not name:
                    raise ValueError('No name in %s' % f)
                while parts and not parts[-1].strip():
                    parts.pop()
                result[name] = ''.join(parts)
                parts.clear()

        for line in lines:
            if line.startswith('###'):
                new_section()
                _, name = line.split()
            else:
                parts.append(line)
        new_section()
        return result

    filename = '/'.join(('src', 'pyx', 'timedata', 'template') + names) + '.pyx'
    sub = substituter(**kwds)

    try:
        parts = read(open(filename), filename)
        return [sub(parts.get(i)) for i in ('declare', 'define')]

    except Exception as e:
        raise e.__class__('in file %s' % filename)
