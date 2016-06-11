### declare
    vector[string]& $name_cpp()

### define
    @staticmethod
    def $name_py():
        cdef vector[string] names = $name_cpp()
        """$documentation"""
        return [i.decode('ascii') for i in names]
