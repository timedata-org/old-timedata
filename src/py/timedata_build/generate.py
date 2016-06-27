#!/usr/bin/env python3

import os
from . import make_from_parts, old_templates, read_structs, util

USE_LISTS = not not False

STRUCT_FILES = [
    'timedata/signal/combiner',
    'timedata/signal/fade',
    'timedata/signal/render3',
    'timedata/signal/stripe',
    ]


def generate():
    print('writing old templates')
    old = old_templates.write()

    print('writing structs')
    structs = read_structs.read_structs(STRUCT_FILES)

    print('writing parts')
    files = make_from_parts.execute()

    print('writing genfiles.pyx')
    if not USE_LISTS:
        files = (f for f in files if 'List' not in f)
    data = ''.join('include "%s"\n' % f for f in files)
    util.write_if_different('build/genfiles/timedata/genfiles.pyx', data)
