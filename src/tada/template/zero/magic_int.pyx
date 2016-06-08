### comment
"""A magic method that returns a C++ int directly."""

### declare
    int magic_$name($class_cpp&)

### define
    def __${name}__($class_py self):
        return magic_$name(self.cdata)
