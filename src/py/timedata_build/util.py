#!/usr/bin/env python3

import contextlib, csv, json, os, pathlib, stat, string, sys


def substituter(**kwds):
    return lambda t: string.Template(t or '').substitute(**kwds)


def make_writable(f, is_writable=True):
    try:
        os.chmod(f, stat.S_IWRITE if is_writable else stat.S_IREAD)
    except:
        pass


def write_if_different(fname, data):
    """Writes a file if it is different from what's there, creating its
       directory if necessary."""
    try:
        old_data = open(fname).read()
    except:
        old_data = None
    if old_data != data:
        os.makedirs(os.path.dirname(fname), exist_ok=True)
        make_writable(fname)
        open(fname, 'w').write(data)
        make_writable(fname, False)
        print('Wrote changed file', fname)
    else:
        print(fname, 'unchanged')


def read_template(lines, f):
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


def substitute_templates(*names, **kwds):
    filename = os.path.join('src', 'pyx', 'timedata', 'template',
                            *names) + '.pyx'
    sub = substituter(**kwds)

    try:
        parts = read_template(open(filename), filename)
        return [sub(parts.get(i)) for i in ('declare', 'define')]

    except Exception as e:
        s = ' '.join(str(i) for i in e.args)
        raise e.__class__('%s in file %s' % (s, filename))


class Context(object):
    def __init__(self, **kwds):
        for (k, v) in kwds.items():
            setattr(self, k, v)


def substitute_context(context, **kwds):
    context = dict(context)
    sub = substituter(**kwds)

    for k, v in context.pop('substitutions', {}).items():
        context[k] = sub(v)
    return Context(**context)


def add_methods(x=None, **y):
    """Merge two dictionaries down exactly two levels."""
    import copy
    def tup(v):
        return (v, ) if isinstance(v, str) else v

    result = copy.deepcopy(x or {})
    for k, v in y.items():
        if k == 'base':
            result[k] = result.get(k, ()) + tup(v)
        else:
            r_value = result.setdefault(k, {})
            for k2, v2 in v.items():
                v3 = r_value.get(k2, ())
                r_value[k2] = v3  + tup(v2)
    return result
