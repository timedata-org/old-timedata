#!/usr/bin/env python3

import datetime, os, sys

MAKE_PYX = """\
/development/make_pyx/make_pyx.py \
    tdsp/signal/fade.h \
    tdsp/signal/combiner.h \
    tdsp/signal/stripe.h\
"""

if __name__ == '__main__':
    root = 'src/tdsp/color/color_list'
    template_file = root + '.template.pyx'
    TEMPLATE = open(template_file).read()

    script = sys.argv[0]
    timestamp = datetime.datetime.utcnow().isoformat()

    class_name, color_class, base = '_ColorList', '_Color', 'normal'

    open(root + '.pyx', 'w').write(TEMPLATE.format(**locals()))

    class_name, color_class, base = '_ColorList256', '_Color256', 'integer'
    open(root + '256.pyx', 'w').write(TEMPLATE.format(**locals()))

    if False:
       os.cwd('src')
       os.system(MAKE_PYX)
