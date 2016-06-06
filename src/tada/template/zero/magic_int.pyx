### comment
"""A magic method that returns a C++ int directly."""

### declare
    int {name}({class_cpp}&)

### define
    def __{name}__({class_py} self):
        """{documentation}"""
        return {name}(self.cdata)
