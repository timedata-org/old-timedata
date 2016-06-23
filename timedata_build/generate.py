#!/usr/bin/env python3

import os

from . import make_from_parts, old_templates, read_structs, util

STRUCT_FILES = [
    'timedata/signal/combiner.h',
    'timedata/signal/fade.h',
    'timedata/signal/render3.h',
    'timedata/signal/stripe.h',
    ]

ROOT = 'src/timedata/template'

def generate():
    old = old_templates.write()
    structs = read_structs.read_structs(STRUCT_FILES)
    structs = ['src/' + s for s in structs]
    colors, lists = make_from_parts.execute(ROOT)

    files = colors # + lists
    data = ''.join('include "%s"\n' % f for f in files)
    f = os.path.join(ROOT, 'genfiles.pyx')
    util.write_if_different(f, data)
