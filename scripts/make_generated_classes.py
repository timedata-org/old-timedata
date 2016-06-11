#!/usr/bin/env python3

import datetime, os, sys, new_templates, template
from read_structs import read_structs

MAKE_PYX = """\
/development/make_pyx/make_pyx.py \
    tada/signal/fade.h \
    tada/signal/combiner.h \
    tada/signal/render3.h\
    tada/signal/stripe.h\
"""

STRUCTS = 'fade', 'combiner', 'render3', 'stripe'

STRUCT_FILES = ['tada/signal/%s.h' % i for i in STRUCTS]

FILES = 'src/tada/color/color', 'src/tada/color/color_list'

def write_old_templates():
    script = sys.argv[0]
    timestamp = datetime.datetime.utcnow().isoformat()
    for suffix, base, ratio in (('', 'normal', '1.0'),
                                ('256', 'integer', '255.0')):
        for f in FILES:
            template_file = f + '.template.pyx'
            template = open(template_file).read()
            open(f + suffix + '.pyx', 'w').write(template.format(**locals()))

def write_make_pyx_templates():
    os.chdir('src')
    try:
        read_structs.read_structs(STRUCT_FILES, template)
    finally:
        os.chdir('..')

def write_new_templates():
    new_templates.execute('src/tada/template')


if __name__ == '__main__':
    write_old_templates()
    write_make_pyx_templates()
    write_new_templates()
