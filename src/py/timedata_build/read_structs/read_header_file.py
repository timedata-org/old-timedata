import re

class Context(object):
    def __init__(self, **kwds):
        for (k, v) in kwds.items():
            setattr(self, k, v)


def read_header_file(header_file):
    context = Context(
        namespaces=[],
        structs=[],
        classname='',
        enum_classes=[],
        enums=[],
        declarations=[],
        )

    def clean_struct(s):
        typename, *parts = s.split()

        was_equal = False
        variables = []
        for p in parts:
            if p[-1] in ';,':
                p = p[:-1]
            was_equal or p == '=' or variables.append(p)
            was_equal = p == '='

        assert typename and parts and variables
        return Context(typename=typename, variables=variables)

    def struct_is_finished(line):
        return ('{' in line or
                '(' in line or
                line.startswith('};') or
                line.startswith('class') or
                line.startswith('static') or
                line.startswith('template'))

    def strip_comments_and_empties(f):
        for line in f:
            comment = line.find('//')
            if comment >= 0:
                line = line[:comment]
            line = line.strip()
            if line:
                 yield line

    regex = Context(
        namespace=re.compile(r'namespace (\w+)'),
        cstruct=re.compile(r'struct (\w+)'),
        enum_class=re.compile(r'enum class (\w+) \{([^}]+)}'),
        )

    in_struct = False
    for line in strip_comments_and_empties(open(header_file)):
        if in_struct:
            m = regex.enum_class.match(line)
            if m:
                context.enum_classes.append(m.group(1, 2))
            elif struct_is_finished(line):
                break
            else:
                context.structs.append(clean_struct(line))
        else:
            m = regex.namespace.match(line)
            if m:
                context.namespaces.append(m.group(1))
            else:
                m = regex.cstruct.match(line)
                if m:
                    context.classname = m.group(1)
                    in_struct = True

    return context
