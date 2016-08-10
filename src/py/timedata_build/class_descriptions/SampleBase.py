from . Base import *

value_type = 'float'

methods = add_methods(
    methods,
    base='sample',
    zero=dict(
        magic=('abs', 'ceil', 'floor', 'invert', 'neg', 'round', 'trunc',),
        magic_int=('hash',),
        ),

    one=dict(
        magic_arithmetic=('add', 'truediv', 'mod', 'mul', 'sub', ),

        return_class=(
            ('limit_max',
             'Return a new $classname whose components are limited above by x'),
            ('limit_min',
             'Return a new $classname whose components are limited below by x'),
            ),

        return_number=(
            ('distance',
             'Return the distance between this $classname and x.'),
            ('distance2',
             """Return the square of the distance between this $classname and x.
            This is significantly faster than the distance method."""),
            ),

        return_class_from_int=(
            ('rotated',
             'Return a new $classname with the components cyclically rotated '
             'by `index` places.'),
            ),
        # no divmod!
	),

    three=dict(
        magic=('pow',),
        ),
    )
