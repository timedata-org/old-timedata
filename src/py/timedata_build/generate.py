#!/usr/bin/env python3

import os
from . import read_classes, write_class, make_structs, files


STRUCT_FILES = ['timedata/signal/render3']


def generate(tiny=False, models=''):
    filenames = list(make_structs.make_structs(STRUCT_FILES))

    for c in read_classes.read_classes(tiny=tiny, models=models):
        if not False and 'Remap' in c.output_file:
            continue
        filenames.append(write_class.write_class(c.methods, **c.__dict__))

    data = ''.join('include "%s"\n' % f for f in sorted(filenames))
    files.write_if_different('build/genfiles/timedata/genfiles.pyx', data)
