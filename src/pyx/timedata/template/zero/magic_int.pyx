### comment
"""A magic method that returns a C++ int directly."""

### declare
    int magic_$name(C$classname&)

### define
    def __${name}__($classname self):
        """Python magic method __${name}__."""
        return magic_$name(self.cdata)
