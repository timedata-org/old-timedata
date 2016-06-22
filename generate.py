#!/usr/bin/env python3

from timedata_build import make_from_parts, old_templates, read_structs

STRUCT_FILES = [
    'timedata/signal/combiner.h',
    'timedata/signal/fade.h',
    'timedata/signal/render3.h',
    'timedata/signal/stripe.h',
    ]

def generate():
    old_templates.write()
    read_structs.read_structs(STRUCT_FILES)
    make_from_parts.execute('src/timedata/template')

if __name__ == '__main__':
    generate()
