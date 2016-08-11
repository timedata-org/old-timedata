#!/usr/bin/env python3

import os
from . import read_classes, write_classes, make_structs, files


STRUCT_FILES = ['timedata/signal/render3']


def generate(tiny=False, models=''):
    filenames = list(make_structs.make_structs(STRUCT_FILES))
    for c in read_classes.read_classes(tiny=tiny, models=models):
        filenames.append(write_classes.write_classes(c.methods, **c.__dict__))

    data = ''.join('include "%s"\n' % f for f in sorted(filenames))
    files.write_if_different('build/genfiles/timedata/genfiles.pyx', data)
