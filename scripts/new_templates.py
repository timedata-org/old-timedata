import collections, copy, instantiations, string, sys, template

SAMPLE_DEFAULTS = dict(
    base=('base', 'fixed_length'),
    zero=dict(
        magic=('abs', 'ceil', 'floor', 'invert', 'neg', 'round', 'trunc'),
        magic_int=('hash',)),

    one=dict(
        magic_arithmetic=('add', 'truediv', 'mod', 'mul', 'sub'),
        return_class=('limit_min', 'limit_max'),
        return_number=('distance', 'distance2'),
        return_class_from_int=('rotated',)),
        # no divmod!

    two=dict(magic=('pow',)),
)


def write(root, config, *, output_file=None, **kwds):
    declare, define = [], []

    def fmt(*names, **kwds):
        dc, df = template.format(root, *names, **kwds)
        dc and declare.append(dc)
        df and define.append(df)

    for b in config['base']:
        fmt('base', b, **kwds)

    for i, name in enumerate(kwds.get('properties', ())):
        fmt('zero', 'property', name=name, index=i, **kwds)

    for method_type in 'zero', 'one', 'two', 'static':
        for tmpl, methods in sorted(config.get(method_type, {}).items()):
            for m in methods:
                if not isinstance(m, dict):
                    m = dict(name=m)
                fmt(method_type, tmpl, **collections.ChainMap(m, kwds))

    while define and not define[-1].strip():
        define.pop()

    with open(output_file, 'w') as f:
        f.writelines(d for d in declare if d.strip())
        f.write('\n' + '\n'.join(define))
    return output_file

def execute(root):
    for c in (instantiations.Color,):
        context = copy.copy(SAMPLE_DEFAULTS)
        context.update(**c.methods)
        f = write(root, context, **c.__dict__)
        print('wrote file', f)

if __name__ == '__main__':
    execute(sys.argv[1])
