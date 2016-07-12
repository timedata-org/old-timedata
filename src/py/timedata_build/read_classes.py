from . class_descriptions import Color, ColorList
from . util import substitute_context

MODELS = (
    ('RGB', ('red', 'green', 'blue')),
    ('HSL', ('hue', 'saturation', 'lightness')),
    ('HSV', ('hue', 'saturation', 'value')),
    ('XYZ', ('x', 'y', 'z')),
    ('YIQ', ('luma', 'inphase', 'quadrature')),
    ('YUV', ('luma', 'uchrominance', 'vchrominance')),
    )

def read_classes(tiny=False, models=[]):
    for model, prop in MODELS:
        for range_name in '', '255', '256':
            name = model + range_name

            if models:
                if name.lower() not in models:
                    continue
            elif tiny:
                if range_name or (model not in ('RGB', 'HSV')):
                    continue
            else:
                if range_name and model != 'RGB':
                    continue

            def sub(cl, name, **kwds):
                return substitute_context(
                    cl.__dict__, name=name, properties=prop,
                    range=float(range_name or '1'), **kwds)

            cname = 'Color' + name
            lname = 'ColorList' + name

            yield sub(Color, cname)
            yield sub(ColorList, lname, sampleclass=cname)
