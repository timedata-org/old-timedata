#!/usr/bin/env python3

from tada_build import make_from_parts, old_templates, read_structs

STRUCT_FILES = [
    'tada/signal/combiner.h',
    'tada/signal/fade.h',
    'tada/signal/render3.h',
    'tada/signal/stripe.h',
    ]

def generate():
    old_templates.write()
    read_structs.read_structs(STRUCT_FILES)
    make_from_parts.execute('src/tada/template')

if __name__ == '__main__':
    generate()
