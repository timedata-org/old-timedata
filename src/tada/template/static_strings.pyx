### declare
    vector[string] {function_cpp}()

### define
    @staticmethod
    def {function_py}():
        """{documentation}"""
        cdef vector[string] names
        result = []
        names = {function_cpp}()
        for i in names:
            result.append(i.decode('ascii'))
        return result
