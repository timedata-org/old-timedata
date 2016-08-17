from . Base import *

start = 0
include_file = 'timedata/color/cython_list_inl.h'
namespace = 'timedata::color_list'

methods = add_methods(
    base=('base', 'list', 'copy'),
    zero=dict(
        simple_mutator=('clear', 'zero'),
        python_mutator='reverse',
        ),

    one=dict(return_number=('distance', 'distance2')),
    two=dict(magic='add', mul='mul'),
)
