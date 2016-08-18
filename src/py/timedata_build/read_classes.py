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
    mutable_dict = class_descriptions.Mutable.__dict__
    color_list_dict = class_descriptions.ColorList.__dict__
    results = []

    def read_class(model, properties, range_name):
        name = model + range_name
        color_name = 'Color' + name
        mutable_name = 'Mutable' + color_name

        if models:
            if name.lower() not in models:
                return
        elif tiny:
            if range_name or (model not in ('RGB', 'HSV')):
                return
        else:
            if range_name and model != 'RGB':
                return

        def sub(cl, name, **props):
            context = dict(cl, **props)
            sub = template.substituter(
                name=name,
                range=range_name or '1',
                mutableclass=mutable_name,
                sampleclass=color_name)

            for k, v in context.pop('substitutions', {}).items():
                context[k] = sub(v)
            results.append(Context(**context))

        sub(color_dict, color_name, properties=properties)
        sub(mutable_dict, mutable_name, mutable_properties=properties,
            parentclass=color_name)
        sub(color_list_dict, 'ColorList' + name)

    for model, prop in MODELS:
        for range_name in '', '255', '256':
            read_class(model, prop, range_name)

    results.append(class_descriptions.Remap)
    return results
