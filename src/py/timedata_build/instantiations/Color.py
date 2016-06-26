from . SampleBase import *
from timedata_build import util

start = 0
compare = 'compare'
from_string = 'stringToColor'
to_string = 'colorToString'
include_file = 'timedata/color/cython_inl.h'
properties = 'red', 'green', 'blue'
namespace = 'timedata::color'
size = 3
documentation = 'FIXME'
fix_key = 'fixKey'

methods = add_methods(
    methods,

    static=dict(
        strings=(
            dict(name_cpp='colorNames',
                 name_py='names',
                 documentation='Return a list all names for colors'),
            ),
        from_cpp=(
            dict(name='from_hex',
                 argument_type='uint32_t',
                 documentation='Create a color from a hex integer'),
            ),
        ),

    zero=dict(
        return_cpp=(
            dict(name='to_hex',
                 return_type='uint32_t',
                 documentation='Return the nearest hex for this color'),
            ),
        ),
    )

substitutions = dict(substitutions,
                     class_documentation="""\
A $class_py is an immutable RGB floating point color.

     A $class_py looks very much like a Python tuple with three floating point
     numbers, with the big exception that operators like + and * perform
     arithmetic, not list-style operations.

     The constructor for $class_py takes a triple of numbers but also strings
     representing human-readable color names like "red" and "green".

     $class_py supports the operations +, -, *, /, %, pow, and ~ (which means
     "take the complementary color").

     ${class_py}s are very lightweight - about half the size of a corresponding
     Python tuple and more than twice as fast to create and copy.  ${class_py}s
     are also immutable - all operations on ${class_py}s have to create a new
     $class_py.

     The expected range of components in the color is from 0 to $range but
     it's perfectly acceptable to have any value in intermediate calculations,
     even infinity.""",
     )

_locals = dict(locals())

Color = util.substitute_context(_locals, class_py='Color', range='1')
Color255 = util.substitute_context(_locals, class_py='Color255', range='255')
Color256 = util.substitute_context(_locals, class_py='Color256', range='256')

__all__ = 'Color', 'Color255', 'Color256'
