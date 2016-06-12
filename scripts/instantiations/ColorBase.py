begin = 0
compare = 'compare'
from_string = 'stringToColor'
to_string = 'colorToString'
include_file = 'tada/color/cython_inl.h'
properties = 'red', 'green', 'blue'
namespace = 'tada::color'
value_type = 'float'
size = 3
documentation = 'FIXME'
fix_key = 'fixKey'

methods = dict(
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

class_documentation = """A Color is an immutable RGB floating point color.

       A Color looks very much like a Python tuple with three floating point
       numbers, with the big exception that operators like + and * perform
       arithmetic, not list-style operations.

       The constructor for Color takes a triple of numbers but also strings
       representing human-readable color names like "red" and "green".

       Color supports the operations +, -, *, /, %, pow, and ~ (which means
       "take the complementary color").

       Colors are very lightweight - about half the size of a corresponding
       Python tuple and more than twice as fast to create and copy.  Colors are
       also immutable - all operations on Colors have to create a new Color.
    """
