#!/usr/bin/env python3

import datetime, os, sys

MAKE_PYX = """\
/development/make_pyx/make_pyx.py \
    tdsp/signal/fade.h \
    tdsp/signal/combiner.h \
    tdsp/signal/stripe.h\
"""

FILES = 'src/tdsp/color/color', 'src/tdsp/color/color_list'

if __name__ == '__main__':
    script = sys.argv[0]
    timestamp = datetime.datetime.utcnow().isoformat()
    for suffix, base, ratio in (('', 'normal', '1.0'),
                                ('256', 'integer', '255.0')):
        for f in FILES:
            template_file = f + '.template.pyx'
            template = open(template_file).read()
            open(f + suffix + '.pyx', 'w').write(template.format(**locals()))


    if False:
       os.cwd('src')
       os.system(MAKE_PYX)
