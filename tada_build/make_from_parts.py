import collections, os, string, sys

from . import instantiations, templates

def write(root, config, *, output_file=None, **kwds):
    declare, define = [], []

    def fmt(*names, **kwds):
        dc, df = templates.substitute(root, *names, **kwds)
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
    files = []
    for c in (instantiations.Color,
              instantiations.Color255,
              instantiations.Color256):
        f = write(root, c.methods, **c.__dict__)
        print('Wrote file', f)
        files.append(f)
    f = os.path.join(root, 'genfiles.pyx')
    open(f, 'w').writelines('include "%s"\n' % f for f in files)
    print('Wrote genfile', f)
