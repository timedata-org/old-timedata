from . import class_descriptions, template
from . context import Context


MODELS = (
    ('RGB', ('red', 'green', 'blue')),
    ('HSL', ('hue', 'saturation', 'lightness')),
    ('HSV', ('hue', 'saturation', 'value')),
    ('XYZ', ('x', 'y', 'z')),
    ('YIQ', ('luma', 'inphase', 'quadrature')),
    ('YUV', ('luma', 'uchrominance', 'vchrominance')),
    )


def read_classes(tiny=False, models=[]):
    color_dict = class_descriptions.Color.__dict__
    color_list_dict = class_descriptions.ColorList.__dict__

    def substitute_context(context, **kwds):
        context = dict(context)
        sub = template.substituter(**kwds)

        for k, v in context.pop('substitutions', {}).items():
            context[k] = sub(v)
        return Context(**context)

    def read_class(model, properties, range_name):
        name = model + range_name

        if models:
            if name.lower() not in models:
                return
        elif tiny:
            if range_name or (model not in ('RGB', 'HSV')):
                return
        else:
            if range_name and model != 'RGB':
                return
        range_name = range_name or '1'

        def sub(cl, name, **kwds):
            return substitute_context(
                cl, name=name, range=range_name, **kwds)

        cname = 'Color' + name
        lname = 'ColorList' + name
        yield sub(dict(color_dict, properties=properties), cname)
        yield sub(color_list_dict, lname, sampleclass=cname)

    for model, prop in MODELS:
        for range_name in '', '255', '256':
            yield from read_class(model, prop, range_name)
