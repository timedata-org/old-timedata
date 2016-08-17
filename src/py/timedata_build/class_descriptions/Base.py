def add_methods(old_methods=None, **new_methods):
    """Merge two class description dictionaries."""
    import copy
    def tup(v):
        return (v, ) if isinstance(v, str) else tuple(v)

    result = copy.deepcopy(old_methods or {})
    for signature, categories in new_methods.items():
        if signature == 'base':
            result['base'] = result.get('base', ()) + tup(categories)
        else:
            cat_dict = result.setdefault(signature, {})
            for category, methods in categories.items():
                cat_dict[category] = cat_dict.get(category, ()) + tup(methods)
    return result


number_type = 'float'
model = 'RGB'

substitutions = dict(
    classname='$name',
    output_file='build/genfiles/timedata/color/$name.pyx',
    range='$range',
    )
