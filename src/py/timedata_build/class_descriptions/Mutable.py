from . Base import *

methods = add_methods(
    base='mutable',

    static=dict(
        from_cpp=(
            dict(name='from_hex',
                 argument_type='uint32_t',
                 documentation='Create a $classname from a hex integer'),
            ),
        ),

    zero=dict(
        arithmetic=('abs', 'ceil', 'floor', 'invert', 'neg', 'round', 'trunc'),
        ),

    one=dict(
        magic_mutable=('add', 'truediv', 'mod', 'mul', 'sub', ),
        ),
    )

substitutions = dict(
    substitutions,
    sampleclass='$sampleclass',
    )
class_documentation = """A mutable version of $parentclass."""
