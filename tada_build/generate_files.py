#!/usr/bin/env python3

import datetime, os, sys, new_templates
from read_structs import read_structs

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


if __name__ == '__main__':
    write_old_templates()
    os.chdir('src')
    read_structs.read_structs(STRUCT_FILES,
                              new_templates.substitute_template)
    os.chdir('..')
    new_templates.execute('src/tada/template')
