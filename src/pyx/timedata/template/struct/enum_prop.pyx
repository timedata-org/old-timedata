### define
    property $prop:
        def __get__(self):
            return self.${TYPE}_NAMES[<int> self.cdata.$prop]

        def __set__(self, object x):
            cdef uint8_t i
            try:
                if isinstance(x, str):
                    i = self.${TYPE}_NAMES.index(x)
                elif isinstance(x, Number) and 0 <= x < len(self.${TYPE}_NAMES):
                    i = x
                else:
                    raise ValueError()
                self.cdata.$prop = <$Type>(i)
            except ValueError:
                raise ValueError('%s is not a valid value '
                                 'for $classname::$Type' % x)
