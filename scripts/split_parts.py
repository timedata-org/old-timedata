#!/usr/bin/env python3

import csv, json, sys

# Split parts as in src/tada/signal/parts.pyx

def split(lines):
    parts = []
    result = {}
    first = not True

    def new_section():
        def r(s):
            return s.strip()
        if parts:
            result.setdefault(name, {})[action] = ''.join(parts)
            parts.clear()
    for line in lines:
        if line.startswith('###'):
            new_section()
            _, action, name = line.split()
        elif (not parts) or line.strip() or parts[-1].strip():
            parts.append(line)
    new_section()
    return result

def pretty_split(lines):
    for name, d in sorted(split(lines).items()):
        for action, value in sorted(d.items()):
            print('%s: %s:' % (action, name))
            print(value, end='')


if __name__ == '__main__':
    pretty_split(open(sys.argv[1]))
