import collections, copy, instantiations, os, read_templates, string, sys

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

def substitute_template(*names, **kwds):
    filename = os.path.join(*names) + '.pyx'
    try:
        parts = read_templates.read(open(filename), filename)
        def _sub(name):
            return string.Template(parts.get(name, '')).substitute(**kwds)
        return _sub('declare'), _sub('define')

    except Exception as e:
        s = ' '.join(str(i) for i in e.args)
        raise e.__class__('%s in file %s' % (s, filename))

def merge_context(x, y):
    """Merge two dictionaries down exactly two levels."""
    result = copy.copy(x)
    for k, v in y.items():
        r_value = result.setdefault(k, {})
        for k2, v2 in v.items():
            r_value[k2] = r_value.get(k2, ()) + v2
    return result

def write(root, config, *, output_file=None, **kwds):
    declare, define = [], []

    def fmt(*names, **kwds):
        dc, df = substitute_template(root, *names, **kwds)
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
        context = merge_context(SAMPLE_DEFAULTS, c.methods)
        f = write(root, context, **c.__dict__)
        print('Wrote file', f)

if __name__ == '__main__':
    execute(sys.argv[1])
