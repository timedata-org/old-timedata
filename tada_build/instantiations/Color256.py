from . ColorBase import *

class_cpp = 'ColorCpp256'
class_py = 'NewColor256'
output_file = 'src/tada/color/color256.gen.pyx'
range = 256.0

class_documentation += """
        NewColor is a normalized color class, with components having a
        range of [0, 1]
    """
