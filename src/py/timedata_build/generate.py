#!/usr/bin/env python3

import os
from . import make_classes, make_structs, util


STRUCT_FILES = [
    'timedata/signal/combiner',
    'timedata/signal/fade',
#    'timedata/signal/render3',
    'timedata/signal/stripe',
    ]


def generate():
    structs = make_structs.make_structs(STRUCT_FILES)
    classes = list(make_classes.make_classes())

    data = ''.join('include "%s"\n' % f for f in sorted(structs + classes))
    util.write_if_different('build/genfiles/timedata/genfiles.pyx', data)
