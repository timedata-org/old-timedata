import os, sys

from collections import ChainMap

from instantiations import Color
import split_parts

# These are all of Python's "magic" arithmetic functions with zero arguments.

SAMPLE_DEFAULTS = dict(
    base=('base', 'fixed_length'),
    zero=dict(
        magic=('abs', 'ceil', 'floor', 'invert', 'neg', 'round', 'trunc'),
        magic_int=('hash',),
        ),

    one=dict(
        magic_arithmetic=('add', 'truediv', 'mod', 'mul', 'sub'),
        return_class=('limit_min', 'limit_max'),
        return_number=('distance', 'distance2'),
        return_class_from_int=('rotate',),
        ),
        # no divmod!

    two=dict(
        return_class=('pow',)
        ),
)

COLOR_DEFAULTS = dict(
    static=dict(
        strings=(dict(name_cpp='colorNames', name_py='names'),),
        ),
        **SAMPLE_DEFAULTS
    )


def write(root, config, **kwds):
    results = []
    sections = 'declare', 'define'
    def add(*names, **kwds):
        filename = os.path.join(root, *names) + '.pyx'
        parts = split_parts.split(open(filename), filename)
        try:
            results.append([parts[n].format(**kwds) for n in sections])
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

    return '\n'.join('\n'.join(i) for i in zip(*results))


def execute(root):
    return write(root, COLOR_DEFAULTS, **Color.__dict__)

if __name__ == '__main__':
    print(execute(sys.argv[1]))
