def _add_classes(d):
    from . import Color, ColorList
    from .. util import substitute_context as _sub

    """Automatically generate classes.  This is a bit overkill now but
       will be necessary when we have half-a-dozen color models."""
    results = {}
    for name in '', '255', '256':
        cname = 'Color' + name
        lname = 'ColorList' + name
        results[cname] = _sub(
            Color.__dict__, name=cname, range=name or '1')
        results[lname] = _sub(
            ColorList.__dict__, name=lname, sample_name=cname, range=name or '1')
    return results

_classes = _add_classes(locals())
locals().update(_classes)
__all__ = tuple(_classes.keys())
