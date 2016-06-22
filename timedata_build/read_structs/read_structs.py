#!/usr/bin/env python3

import datetime, os, re, string, sys

from . read_header_file import read_header_file, Context
from . make_enums import make_enums
from .. import templates


def make(header_file):
    header = read_header_file(header_file)
    classname = header.classname
    namespace = ':'.join(header.namespaces)
    member_name = '_instance'

    enum_class, enum_pyx, enum_types = make_enums(
        header.enum_classes, header_file, namespace, header.classname)

    indent = '\n        '
    fmt = lambda s: s.typename + ' ' + ', '.join(s.variables)
    pyx_structs = indent.join(fmt(s) for s in header.structs)
    if pyx_structs:
        pyx_structs = indent + pyx_structs

    struct_definition = '    struct %s:%s' % (classname, pyx_structs)
    props = []

    variables_to_enum_type = {}

    for s in header.structs:
        if s.typename in enum_types:
            for i in s.variables:
                variables_to_enum_type[i] = s.typename
        props += s.variables

    str_format = [n + ("='%s'" if n in variables_to_enum_type else '=%s')
                  for n in props]
    str_format = ', '.join(str_format)
    variable_names = ', '.join('self.' + n for n in props)
    property_list = []

    def format(s, kwds):
        x, y = templates.substitute('timedata', 'template', 'struct', s, **kwds)
        return x + '\n' + y if False else x + y

    for s in header.structs:
        for prop in s.variables:
            if prop in variables_to_enum_type:
                Type = variables_to_enum_type[prop]
                TYPE = Type.upper()
                tmpl = 'enum_prop'
            else:
                tmpl = 'prop'
            typename, variables = s.typename, s.variables
            property_list.append(format(tmpl, locals()))

    property_list = '\n'.join(property_list)
    timestamp = datetime.datetime.utcnow().isoformat()
    mt = enum_class
    if property_list:
        if mt:
            mt += '\n'
        mt += format('class', locals())
    return mt


def read_structs(files):
    os.chdir('src')
    for f in files:
        assert f.endswith('.h'), 'Not a header file: ' + f
        data = make(f)
        base, fname = os.path.split(os.path.splitext(f)[0])
        outfile = os.path.join(base, '_' + fname + '.pyx')
        open(outfile, 'w').write(data)
    os.chdir('..')
