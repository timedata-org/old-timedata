def _add_classes(d):
    """Automatically generate classes.  This is a bit overkill now but
       will be necessary when we have half-a-dozen color models."""
    from . import Color, ColorList
    from .. util import substitute_context

    def sub(cl, name, **kwds):
        results[name] = substitute_context(cl.__dict__, name=name, **kwds)

    results = {}
    for model, prop in (
            ('RGB', ('red', 'green', 'blue')),
            ('HSV', ('hue', 'saturation', 'value')),
            ):
        for name in '', '255', '256':
            cname = 'Color' + model + name
            lname = 'ColorList' + model + name
            rng = float(name or '1')

            sub(Color, cname, range=rng, properties=prop)
            sub(ColorList, lname, range=rng, sampleclass=cname, properties=prop)
    return results


_classes = _add_classes(locals())
locals().update(_classes)
__all__ = tuple(_classes.keys())
