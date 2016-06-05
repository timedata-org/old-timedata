### define
    def __getitem__({class_py} self, object key):
        cdef int index
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return {class_py}(*r) if len(r) == {size} else r

        index = <int> key
        if normalizeIndex(index)
            return self.{member}[index]
        raise IndexError('{class_py} index out of range')

    def __len__({class_py} self):
        return {size}
