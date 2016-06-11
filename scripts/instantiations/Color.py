begin = 0
class_cpp = 'ColorCpp'
class_py = 'NewColor'
compare = 'compare'
from_string = 'stringToColor'
to_string = 'colorToString'
include_file = 'tada/color/cython_inl.h'
output_file = 'src/tada/color/color.gen.pyx'
properties = 'red', 'green', 'blue'
namespace = 'tada::color'
value_type = 'float'
range = 1.0
size = 3
documentation = ''  # FIX!
fix_key = 'fixKey'

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

       There are two ranges for color components.  The base class Color is
       normalized so that the standard range for output signals - that is,
       outout color components - is [0.0, 1.0].  As always, intermediate signals
       can be greater than 1 or even negative.

       The derived class Color256 has a standard output range of [0, 255] for
       better compatibility with existing RGB and DMX systems.
    """
