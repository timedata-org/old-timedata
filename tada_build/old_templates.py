#!/usr/bin/env python3

import datetime

FILES = 'src/tada/color/color', 'src/tada/color/color_list'

def write():
    timestamp = datetime.datetime.utcnow().isoformat()
    for suffix, base, ratio in (('', 'normal', '1.0'),
                                ('256', 'integer', '255.0')):
        for f in FILES:
            template_file = f + '.template.pyx'
            template = open(template_file).read()
            try:
                open(f + suffix + '.pyx', 'w').write(template.format(**locals()))
            except Exception as e:
                s = ' '.join(str(i) for i in e.args)
                raise e.__class__('%s in file %s' % (s, template_file))
