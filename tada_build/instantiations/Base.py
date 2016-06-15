value_type = 'float'
documentation = 'FIXME'

def add_methods(x=None, **y):
    """Merge two dictionaries down exactly two levels."""
    import copy

    result = copy.deepcopy(x or {})
    for k, v in y.items():
        if k == 'base':
            result[k] = result.get(k, ()) + v
        else:
            r_value = result.setdefault(k, {})
            for k2, v2 in v.items():
                r_value[k2] = r_value.get(k2, ()) + v2
    return result

methods = add_methods({}, base=('base',))
