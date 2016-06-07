
### declare
   void $name($class_cpp, size_t, $element_cpp)

### define
    @staticmethod
    def $name(*args):
        """$documentation"""
        cdef $class_py cl = $class_py()
        cdef size_t last_number = 0

        def accumulate(item=None):
            nonlocal last_number
            if last_number:
                e = $element_py(item)
                $name(cl.cdata, last_number - 1, e$element_member)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                accumulate(a)

        # Spread to "black" if the last element is a number.
        accumulate()
        return cl
