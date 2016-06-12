#!/usr/bin/env python3

import csv, json, os, pathlib, string, sys

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


def substitute(*names, **kwds):
    filename = os.path.join(*names) + '.pyx'
    try:
        parts = read(open(filename), filename)
        def _sub(name):
            return string.Template(parts.get(name, '')).substitute(**kwds)
        return _sub('declare'), _sub('define')

    except Exception as e:
        s = ' '.join(str(i) for i in e.args)
        raise e.__class__('%s in file %s' % (s, filename))
