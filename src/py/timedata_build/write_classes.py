import collections
from . import files, template


def write_classes(config, *, output_file=None, **kwds):
    declare, define = [], []

    def fmt(*names, **kwds):
        name = kwds.get('name')
        docnames = names + (name, ) if name else names
        default_documentation = '.'.join(docnames)
        kwds['documentation'] = kwds.get('documentation', default_documentation)
        dc, df = template.substitute(*names, **kwds)
        dc and declare.append(dc)
        df and define.append(df)

    for b in config['base']:
        fmt('base', b, **kwds)

    for prop in 'properties', 'mutable_properties':
        for i, name in enumerate(kwds.get(prop, ())):
            fmt('zero', prop, name=name, index=i, **kwds)

    for method_type in 'zero', 'one', 'two', 'static':
        for tmpl, methods in sorted(config.get(method_type, {}).items()):
            for m in methods:
                if isinstance(m, str):
                    m = dict(name=m)
                elif isinstance(m, (list, tuple)):
                    name, documentation = m
                    m = dict(name=name, documentation=documentation)
                fmt(method_type, tmpl, **collections.ChainMap(m, kwds))

    while define and not define[-1].strip():
        define.pop()

    data = ''.join(d for d in declare if d.strip()) + '\n' + '\n'.join(define)
    files.write_if_different(output_file, data)
    return output_file
