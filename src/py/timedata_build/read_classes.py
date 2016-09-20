import itertools, re
from . import class_descriptions, template
from . context import Context


MODELS = dict(
    RGB=('red', 'green', 'blue'),
    HSL=('hue', 'saturation', 'lightness'),
    HSV=('hue', 'saturation', 'value'),
    XYZ=('x', 'y', 'z'),
    YIQ=('luma', 'inphase', 'quadrature'),
    YUV=('luma', 'uchrominance', 'vchrominance'),
    )

SUFFIXES = '', '255', '256'

MATCH = re.compile(r'(\D+)(\d*)').match

ALL_MODELS = [''.join(m) for m in itertools.product(MODELS.keys(), SUFFIXES)]

MODEL_SETTINGS = dict(
    all=ALL_MODELS,
    tiny=['RGB', 'RGB255', 'RGB256', 'HSV'],
    )

def get_models(models=None):
    models = MODEL_SETTINGS.get(models or 'tiny', models)
    return [MATCH(m).groups() for m in sorted(models)]

def read_class(model, range_name):
    properties = MODELS[model]
    name = model + range_name
    immutable_name = 'ColorConst' + name
    mutable_name = 'Color' + name
    list_name = 'ColorList' + name

    def sub(cl, name, **props):
        context = dict(cl.__dict__, **props)
        sub = template.substituter(
            name=name,
            range=range_name or '1',
            mutableclass=mutable_name,
            sampleclass=immutable_name)

        for k, v in context.pop('substitutions', {}).items():
            context[k] = sub(v)
        return context

    yield sub(class_descriptions.Color, immutable_name,
              properties=properties)
    yield sub(class_descriptions.Mutable, mutable_name,
              mutable_properties=properties,
              parentclass=immutable_name)
    yield sub(class_descriptions.ColorList, list_name)


def read_classes(models):
    for model, range_name in get_models(models):
        for c in read_class(model, range_name):
            yield c
    yield class_descriptions.IndexList.__dict__
