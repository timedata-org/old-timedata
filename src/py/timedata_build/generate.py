#!/usr/bin/env python3

import os
from . import make_from_parts, read_structs, util


STRUCT_FILES = [
    'timedata/signal/combiner',
    'timedata/signal/fade',
    'timedata/signal/render3',
    'timedata/signal/stripe',
    ]


def generate():
    structs = read_structs.read_structs(STRUCT_FILES)
    files = make_from_parts.execute()

    data = ''.join('include "%s"\n' % f for f in sorted(files))
    util.write_if_different('build/genfiles/timedata/genfiles.pyx', data)
