### declare
    vector[string] {function_cpp}()

### define
    @staticmethod
    def {function_py}():
        """{documentation}"""
        return [i.decode('ascii') for i in {function_cpp}()]
