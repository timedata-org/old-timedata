from collections import ChainMap

from . instantiations import Color

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
        return_scalar=('distance', 'distance2'),
        take_number=('rotate',),
        ),
        # no divmod!

    two=dict(
        return_class=('pow',)
        ),
)

COLOR_DEFAULTS = dict
    static=dict(
        strings=(dict(function_cpp='colorNames', function_py='names'),),
        ),
    )


def write(templates, *configs, **kwds):
    config = ChainMap(*configs)
    results = []
    def add(name, **kwds):
        results.append([i.format(**kwds) for i in parts[name]])

    for b in config['base']:
        add('base', b, **kwds)

    for i, p in enumerate(config.get('properties', ())):
        add('property', index=i, propname=p, **kwds)

    for args in 'zero', 'one', 'two', 'static':
        for name, functions in sorted(kwds[args].items()):
            for f in functions:
                if not isinstance(f, dict):
                    # If it's not a dictionary, it's just a function name.
                    f = dict(function=f)
                add(arg, name, **ChainMap(f, kwds))

    return results


def execute(templates):
    write_sample(templates, **Color.__dict__)
