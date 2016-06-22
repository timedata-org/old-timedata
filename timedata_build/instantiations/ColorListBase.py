from . Base import *

start = 0
compare = 'compare'
from_string = 'stringToColor'
to_string = 'colorToString'
include_file = 'timedata/color/cython_list_inl.h'
properties = ()
namespace = 'timedata::color'
value_type = 'float'
size = 3
documentation = 'FIXME'
fix_key = 'fixKey'
set_at = 'setAt'
slice_into = 'sliceInto'
slice_out = 'sliceOut'

methods = add_methods(
    methods,
    base='variable_length',
    zero=dict(
        mutator=('abs', 'clear', 'floor', 'ceil', 'invert', 'neg', 'reverse',
                 'trunc', 'zero'),
        ),

    one=dict(
        arithmetic=('add', 'div', 'mul', 'pow', 'sub', 'rdiv', 'rpow', 'rsub'),
        return_number=('distance', 'distance2'),
        return_class=('limit_min', 'limit_max'),
        ),

    two=dict(magic=('add',), mul=('mul')
        ),

    three=dict(
        ),
)

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
"""
