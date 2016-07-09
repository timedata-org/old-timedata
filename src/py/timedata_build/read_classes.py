from . class_descriptions import Color, ColorList
from . util import substitute_context

def read_classes(tiny=False):
    for model, prop in (
            ('RGB', ('red', 'green', 'blue')),
            ('HSV', ('hue', 'saturation', 'value')),
            ('HSL', ('hue', 'saturation', 'lightness')),
            ('YIQ', ('luma', 'inphase', 'quadrature')),
            ('YUV', ('luma', 'uchrominance', 'vchrominance')),
            ):
        for name in '', '255', '256':
            if name and (tiny or model != 'RGB'):
                continue
            if tiny and model not in ('RGB', 'HSV'):
                continue

            cname = 'Color' + model + name
            lname = 'ColorList' + model + name
            rng = float(name or '1')

            def sub(cl, name, **kwds):
                return substitute_context(
                    cl.__dict__, name=name, properties=prop, **kwds)

            yield sub(Color, cname, range=rng)
            yield sub(ColorList, lname, range=rng, sampleclass=cname)
