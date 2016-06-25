#!/usr/bin/env python3

import csv, json, os, pathlib, string, sys


def write_if_different(fname, data):
    """Writes a file if it is different from what's there, creating its
       directory if necessary."""
    try:
        old_data = open(fname).read()
    except:
        old_data = None
    if old_data != data:
        os.makedirs(os.path.dirname(fname), exist_ok=True)
        open(fname, 'w').write(data)
        print('Wrote changed file', fname)
    else:
        print(fname, 'unchanged')


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


def substitute_templates(*names, **kwds):
    filename = os.path.join('src', 'pyx', 'timedata', 'template',
                            *names) + '.pyx'
    try:
        parts = read(open(filename), filename)
        def _sub(name):
            return string.Template(parts.get(name, '')).substitute(**kwds)
        return _sub('declare'), _sub('define')

    except Exception as e:
        s = ' '.join(str(i) for i in e.args)
        raise e.__class__('%s in file %s' % (s, filename))
