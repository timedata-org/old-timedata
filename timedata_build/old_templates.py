#!/usr/bin/env python3

import datetime

FILES = 'src/timedata/color/color', 'src/timedata/color/color_list'

def write():
    results = []
    timestamp = datetime.datetime.utcnow().isoformat()
    for suffix, base, ratio in (('', 'normal', '1.0'),
                                ('256', 'integer', '255.0')):
        for f in FILES:
            template_file = f + '.template.pyx'
            template = open(template_file).read()
            try:
                filename = f + suffix + '.pyx'
                open(filename, 'w').write(template.format(**locals()))
                results.append(filename)
            except Exception as e:
                s = ' '.join(str(i) for i in e.args)
                raise e.__class__('%s in file %s' % (s, template_file))

    return results
