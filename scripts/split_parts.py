#!/usr/bin/env python3

import csv, json, pathlib, sys

# Split parts as in src/tada/signal/parts.pyx

def split(lines, f):
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
            # Remove trailing whitespace
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

def split_files(files):
    return {pathlib.Path(f).stem: split(open(str(f)), f) for f in files}

def pretty_split(parts):
    for name, d in sorted(parts.items()):
        for action, value in sorted(d.items()):
            print('%s: %s:' % (action, name))
            print(value)

def combine_globs(args):
    files = []
    p = pathlib.Path('.')
    for a in args:
        files.extend(p.glob(a))
    return files

def split_globs(args):
    return split_files(combine_globs(args))

if __name__ == '__main__':
    pretty_split(split_globs(sys.argv[1:]))
