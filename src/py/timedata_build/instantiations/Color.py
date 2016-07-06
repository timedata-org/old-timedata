from . SampleBase import *

start = 0.0
include_file = 'timedata/color/cython_inl.h'
properties = 'red', 'green', 'blue'
namespace = 'timedata::color'
size = 3
documentation = 'FIXME'

methods = add_methods(
    methods,

    static=dict(
        from_cpp=(
            dict(name='from_hex',
                 argument_type='uint32_t',
                 documentation='Create a $classname from a hex integer'),
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
A $name is an immutable RGB floating point color.

     A $name looks very much like a Python tuple with $$size floating point
     numbers, with the big exception that operators like + and * perform
     arithmetic, not list-style operations.

     The constructor for $name takes a triple of numbers but also strings
     representing human-readable color names like "red" and "green".

     $name supports the operations +, -, *, /, %, pow, and ~ (which means
     "take the complementary color").

     ${name}s are very lightweight - about half the size of a corresponding
     Python tuple and more than twice as fast to create and copy.  ${name}s
     are also immutable - all operations on ${name}s have to create a new
     $name.

     The expected range of components in the color is from 0 to $range but
     it's perfectly acceptable to have any value in intermediate calculations,
     even infinity.""",
     )
