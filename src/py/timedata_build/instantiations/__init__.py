def _add_classes(d):
    """Automatically generate classes.  This is a bit overkill now but
       will be necessary when we have half-a-dozen color models."""
    from . import Color, ColorList
    from .. util import substitute_context

    def sub(cl, name, **kwds):
        results[name] = substitute_context(cl.__dict__, name=name, **kwds)

    results = {}
    for name in '', '255', '256':
        cname = 'NewColor' + name
        lname = 'NewColorList' + name

        sub(Color, cname, range=name or '1')
        sub(ColorList, lname, range=name or '1', sampleclass=cname)
    return results

_classes = _add_classes(locals())
locals().update(_classes)
__all__ = tuple(_classes.keys())
