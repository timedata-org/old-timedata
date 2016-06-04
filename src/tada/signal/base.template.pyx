cdef class {class_py}:
    """{class_documentation}"""
    cdef {class_cpp} {member}

    def __repr__({class_py} self):
        return '{class_py}(%s)' % str(self)

    def __str__({class_py} self):
        return {to_string}(self.{member}).decode('ascii')

    @property
    def begin({class_py} self):
        """Return the lowest in-band value for this sample."""
        return {begin}

    @property
    def range({class_py} self):
        """Return the range from begin() to the highest in-band value."""
        return {range}

    cpdef {class_py} copy({class_py} self):
        cdef {class_py} s = {class_py}()
        s.{member} = self.{member}
        return s
