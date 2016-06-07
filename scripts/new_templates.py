import os, string, sys

from collections import ChainMap

from instantiations import Color
import split_parts

# These are all of Python's "magic" arithmetic functions with zero arguments.

SAMPLE_DEFAULTS = dict(
    base=('base', 'fixed_length'),
    zero=dict(
        magic=('abs', 'ceil', 'floor', 'invert', 'neg', 'round', 'trunc'),
        magic_int=('hash',)),

    one=dict(
        magic_arithmetic=('add', 'truediv', 'mod', 'mul', 'sub'),
        return_class=('limit_min', 'limit_max'),
        return_number=('distance', 'distance2'),
        return_class_from_int=('rotate',)),
        # no divmod!

    two=dict(return_class=('pow',)),
)

COLOR_DEFAULTS = dict(
    static=dict(
        strings=(dict(name_cpp='colorNames', name_py='names'),),
        ),
        **SAMPLE_DEFAULTS
    )

def write(root, config, *, output_file=None, **kwds):
    declare, define = [], []
    def add(*names, **kwds):
        filename = os.path.join(root, *names) + '.pyx'
        try:
            sub = lambda s: string.Template(s).substitute(**kwds)
            parts = split_parts.split(open(filename), filename)
            declare.append(sub(parts['declare']))
            define.append(sub(parts['define']) + '\n')
        except Exception as e:
            raise e.__class__('%s in file %s' % (''.join(e.args), filename))
    for b in config['base']:
        add('base', b, **kwds)

    for i, name in enumerate(config.get('properties', ())):
        add('zero', 'property', name=name, index=i, **kwds)

    for method_type in 'zero', 'one', 'two', 'static':
        for template, methods in sorted(config.get(method_type, {}).items()):
            for m in methods:
                if not isinstance(m, dict):
                    m = dict(name=m)
                add(method_type, template, **ChainMap(m, kwds))

    with open(output_file, 'w') as f:
        f.writelines(d for d in declare if d.strip())
        f.writelines('\n')
        f.writelines(define)
    return output_file

def execute(root):
    f = write(root, COLOR_DEFAULTS, **Color.__dict__)
    print('wrote file', f)

if __name__ == '__main__':
    execute(sys.argv[1])
