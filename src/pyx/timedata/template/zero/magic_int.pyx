### comment
"""A magic method that returns a C++ int directly."""

### declare
    int magic_$name(C$classname&)

### define
    def __${name}__($classname self):
        """$documentation"""
        return magic_$name(self.cdata)
