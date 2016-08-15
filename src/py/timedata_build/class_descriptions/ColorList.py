from . Base import *

start = 0
include_file = 'timedata/color/cython_list_inl.h'
namespace = 'timedata::color_list'
value_type = 'float'
size = 3

methods = add_methods(
    base=('base', 'sample_list', 'copy'),
    zero=dict(
        simple_mutator=(
            'clear',
            'zero'),

        mutator=(
            'abs',
            'floor',
            'ceil',
            'invert',
            'neg',
            'reverse',
            'trunc',
            ),
        ),

    one=dict(
        arithmetic=(
            'add',
            'div',
            'mul',
            'pow',
            'sub',
            'rdiv',
            'rpow',
            'rsub',
            'max_limit',
            'min_limit',
            ),

        return_number=(
            'distance',
            'distance2',
            ),
        ),

    two=dict(
        magic=(
            'add',
            ),

        mul=(
            'mul',
            ),
        ),
)

substitutions = dict(
    substitutions,
    sampleclass='$sampleclass',
    mutableclass='$mutableclass',
    class_documentation = """\
A list of RGB floating point Colors, with many mutating functions.

       A ColorList looks quite like a Python list of Colors (which look like
       tuples) with the big interface difference that operations like + and *
       perform arithmetic and not list construction.

       Written in C++, this class should consume significantly fewer memory and
       CPU resources than a corresponding Python list, as well as providing a
       range of useful facilities.

       While ColorList provides a full set of functions and operations that
       create new ColorLists, in each case there is a corresponding mutating
       function or operation that works "in-place" with no heap allocations
       at all, for best performance.
""",
    )
