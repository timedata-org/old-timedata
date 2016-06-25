#!/usr/bin/env python3

import datetime, os
from . import util

INPUT_DIR = 'src/pyx/timedata/color'
OUTPUT_DIR = 'build/genfiles/timedata/color'
FILES = 'color', 'color_list'

def write():
    results = []
    timestamp = datetime.datetime.utcnow().isoformat()
    for suffix, base, ratio in (('', 'normal', '1.0'),
                                ('256', 'integer', '255.0')):
        for f in FILES:
            template_file = os.path.join(INPUT_DIR, f + '.template.pyx')
            template = open(template_file).read()
            try:
                filename = os.path.join(OUTPUT_DIR, f + suffix + '.pyx')
                data = template.format(**locals())
                util.write_if_different(filename, data)
                results.append(filename)
            except Exception as e:
                s = ' '.join(str(i) for i in e.args)
                print(os.getcwd())
                raise e.__class__('%s in file %s' % (s, template_file))

    return results
