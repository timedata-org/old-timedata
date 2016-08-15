from . Base import *

methods = add_methods(
    base='mutable',
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
