### declare
    string {to_string}({class_cpp)

### define
    def __repr__({class_py} self):
        return '{class_py}(%s)' % str(self)

    def __str__({class_py} self):
        return {to_string}(self.{member}).decode('ascii')
