from . import template


class Context(object):
    def __init__(self, **kwds):
        for (k, v) in kwds.items():
            setattr(self, k, v)


def add_methods(old_methods=None, **new_methods):
    """Merge two class description dictionaries."""
    import copy
    def tup(v):
        return (v, ) if isinstance(v, str) else v

    result = copy.deepcopy(old_methods or {})
    for signature, categories in new_methods.items():
        if signature == 'base':
            result[signature] = result.get(signature, ()) + tup(categories)
        else:
            cat_dict = result.setdefault(signature, {})
            for category, methods in categories.items():
                cat_dict[category] = cat_dict.get(category, ()) + tup(methods)
    return result
