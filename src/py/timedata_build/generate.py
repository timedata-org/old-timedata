#!/usr/bin/env python3

import os
from . import read_classes, write_class, make_structs, files


def generate(structs, tiny, models, outfile):
    filenames = list(make_structs.make_structs(structs))

    for c in read_classes.read_classes(tiny=tiny, models=models):
        filenames.append(write_class.write_class(c.methods, **c.__dict__))

    data = ''.join('include "%s"\n' % f for f in sorted(filenames))
    files.write_if_different(outfile, data)
