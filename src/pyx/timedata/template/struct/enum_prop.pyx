### define
    property $prop:
        def __get__(self):
            return self.${TYPE}_NAMES[<int> self.$member_name.$prop]
        def __set__(self, object x):
            cdef uint8_t i
            if isinstance(x, str):
                i = self.${TYPE}_NAMES.index(x)
            else:
                i = <uint8_t> x
                if i >= len(self.${TYPE}_NAMES):
                    raise ValueError("Can't understand value " + str(i))
            self.$member_name.$prop = <$Type>(i)
