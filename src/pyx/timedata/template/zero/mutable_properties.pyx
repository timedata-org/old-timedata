### define
    property $name:
        def __get__(self):
            return self.cdata[$index]
        def __set__(self, float x):
            self.cdata[$index] = x
