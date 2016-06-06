### declare
   void {spread_append}({class_cpp}, size_t, {element_cpp})

### define
    @staticmethod
    def spread(*args):
        """{class_documentation}"""
        cdef {class_py} cl = {class_py}()
        cdef {element_py} value
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                e = {element_py}(item)
                {spread_append}(cl.cdata, last_number - 1, e{element_member})
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        # Spread to "black" if the last element is a number.
        spread_append(None)
        return cl
