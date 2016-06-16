    cpdef $class_py append($class_py self, $sample_py c):
        """Append to the list of colors."""
        self.cdata.push_back(c.cdata)
        return self

    cpdef size_t count(self, $sample_py color):
        """Return the number of times a color appears in this list."""
        return count(self.cdata, color.cdata)

    cpdef $class_py extend($class_py self, object values):
        """Extend the colors from an iterator."""
        appendInto($class_py(values).cdata, self.cdata)
        return self

    cpdef index($class_py self, $sample_py color):
        """Returns an index to the first occurance of that Color, or
           raises a ValueError if that Color isn't there."""
        cdef int id = indexOf(self.cdata, color.cdata)
        if id >= 0:
            return id
        raise ValueError('Can\'t find color %s' % color)

    cpdef $class_py insert($class_py self, int key,
                                   $sample_py color):
        """Insert a color before key."""
        insertBefore(self.cdata, key, color.cdata)
        return self

    cpdef $sample_py pop($class_py self, int key = -1):
        """Pop the color at key."""
        cdef $sample_py result = $sample_py()
        if popAt(self.cdata, key, result.cdata):
            return result
        raise IndexError('pop index out of range')

    cpdef $class_py remove(self, $sample_py color):
        """Find and remove a specific color."""
        self.pop(self.index(color))
        return self

    cpdef $class_py resize($class_py self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.cdata.resize(size)
        return self

    cpdef $class_py rotate(self, int pos):
        """In-place rotation of the colors forward by `pos` positions."""
        rotate(self.cdata, pos)
        return self

    cpdef $class_py sort(self, object key=None, bool reverse=False):
        """Sort items."""
        if key is None:
            sortColors(self.cdata)
            if reverse:
                self.reverse()
        else:
            self[:] = sorted(self, key=key, reverse=reverse)
        return self

    cpdef $class_py round(self, uint digits=0):
        """Round each element in each color to the nearest integer."""
        roundColor(self.cdata, digits)
        return self

    cpdef $sample_py max(self):
        """Return the maximum values of each component."""
        cdef ColorS c = maxColor(self.cdata)
        return $sample_py(c.red, c.green, c.blue)

    cpdef $sample_py min(self):
        """Return the minimum values of each component/"""
        cdef ColorS c = minColor(self.cdata)
        return $sample_py(c.red, c.green, c.blue)

    @staticmethod
    def spread(*args):
        """Spreads!"""
        cdef $class_py cl = $class_py()
        cdef $sample_py color
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                color = _to_$sample_py(item)
                spreadAppend(cl.cdata, last_number - 1, color.cdata)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        spread_append(None)
        return cl
