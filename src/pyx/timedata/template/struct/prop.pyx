### define
    property $prop:
        def __get__(self):
            return self.cdata.$prop
        def __set__(self, $typename x):
            self.cdata.$prop = x
