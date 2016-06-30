from numbers import Number

cdef class OldColorList{suffix}:
    """A list of RGB floating point OldColors, with many mutating functions.

       A OldColorList looks quite like a Python list of OldColors (which look like
       tuples) with the big interface difference that operations like + and *
       perform arithmetic and not list construction.

       Written in C++, this class should consume significantly fewer memory and
       CPU resources than a corresponding Python list, as well as providing a
       range of useful facilities.

       While OldColorList provides a full set of functions and operations that
       create new OldColorLists, in each case there is a corresponding mutating
       function or operation that works "in-place" with no heap allocations
       at all, for best performance.

       The base class OldColorList is a list of OldColor, which are normalized to
       [0, 1]; the derived class OldColorList256 is a list of OldColor256, which
       are normalized to [0, 255].
"""
    cdef ColorVector colors

    # Magic methods.
    def __cinit__(self, items=None):
        """Construct a OldColorList with an iterator of items, each of which looks
           like a OldColor."""
        if items is not None:
            if isinstance(items, OldColorList{suffix}):
                self.colors = (<OldColorList{suffix}> items).colors
            else:
                # A list of tuples, OldColors or strings.
                self.colors.resize(len(items))
                for i, item in enumerate(items):
                    self[i] = item

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step, index
        cdef float r, g, b
        cdef OldColorList{suffix} cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            if isinstance(x, OldColorList{suffix}):
                cl = <OldColorList{suffix}> x
            else:
                cl = OldColorList{suffix}(x)
            if sliceIntoVector(cl.colors, self.colors, begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        index = key
        if not self.colors.resolvePythonIndex(index):
            raise IndexError('OldColorList index out of range ' + str(index))
        try:
            if isinstance(x, str):
                x = OldColor{suffix}(x)
            r, g, b = x
            self.colors.setColor(index, r, g, b)
        except:
            raise ValueError('Can\'t convert ' + str(x) + ' to a color')

    def __getitem__(self, object key):
        cdef OldColorS c
        cdef int index
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            cl = OldColorList{suffix}()
            cl.colors = sliceVector(self.colors, begin, end, step)
            return cl

        index = key
        if not self.colors.resolvePythonIndex(index):
            raise IndexError('OldColorList index out of range ' + str(key))

        c = self.colors[index]
        return OldColor{suffix}(c.red, c.green, c.blue)

    def __add__(OldColorList{suffix} self, OldColorList{suffix} cl):
        cdef OldColorList{suffix} result = OldColorList{suffix}()
        result.colors = self.colors
        appendInto(cl.colors, result.colors)
        return result

    def __iadd__(OldColorList{suffix} self, OldColorList{suffix} cl):
        appendInto(cl.colors, self.colors)
        return self

    def __mul__(object self, object other):
        # A little tricky because OldColorList can appear on the left or the
        # right side of the argument.
        cdef size_t mult
        cdef OldColorList{suffix} cl = OldColorList{suffix}()
        if isinstance(self, OldColorList{suffix}):
            cl.colors = (<OldColorList{suffix}> self).colors
            mult = <size_t> other
        else:
            cl.colors = (<OldColorList{suffix}> other).colors
            mult = <size_t> self
        duplicateInto(mult, cl.colors)
        return cl

    def __imul__(OldColorList{suffix} self, size_t mult):
        duplicateInto(mult, self.colors)
        return self

    def __len__(self):
        return self.colors.size()

    def __repr__(self):
        return 'OldColorList{suffix}(%s)' % str(self)

    def __richcmp__(OldColorList{suffix} self, OldColorList{suffix} other, int rcmp):
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    def __sizeof__(OldColorList{suffix} self):
        return self.colors.getSizeOf()

    def __str__(OldColorList{suffix} self):
        return toString(self.colors).decode('ascii')

    # List operations.
    cpdef OldColorList{suffix} append(OldColorList{suffix} self, OldColor{suffix} c):
        """Append to the list of colors."""
        self.colors.push_back(c.color)
        return self

    cpdef OldColorList{suffix} clear(self):
        """Resize the list of colors to 0."""
        self.colors.clear()
        return self

    cpdef OldColorList{suffix} copy(self):
        """Resize a copy of this list."""
        cdef OldColorList{suffix} cl = OldColorList{suffix}()
        cl.colors = self.colors
        return cl

    cpdef size_t count(self, OldColor{suffix} color):
        """Return the number of times a color appears in this list."""
        return count(self.colors, color.color)

    cpdef OldColorList{suffix} extend(OldColorList{suffix} self, object values):
        """Extend the colors from an iterator."""
        appendInto(OldColorList{suffix}(values).colors, self.colors)
        return self

    cpdef index(OldColorList{suffix} self, OldColor{suffix} color):
        """Returns an index to the first occurance of that OldColor, or
           raises a ValueError if that OldColor isn't there."""
        cdef int id = indexOf(self.colors, color.color)
        if id >= 0:
            return id
        raise ValueError('Can\'t find color %s' % color)

    cpdef OldColorList{suffix} insert(OldColorList{suffix} self, int key,
                                   OldColor{suffix} color):
        """Insert a color before key."""
        insertBefore(self.colors, key, color.color)
        return self

    cpdef OldColor{suffix} pop(OldColorList{suffix} self, int key = -1):
        """Pop the color at key."""
        cdef OldColor{suffix} result = OldColor{suffix}()
        if popAt(self.colors, key, result.color):
            return result
        raise IndexError('pop index out of range')

    cpdef OldColorList{suffix} remove(self, OldColor{suffix} color):
        """Find and remove a specific color."""
        self.pop(self.index(color))
        return self

    cpdef OldColorList{suffix} resize(OldColorList{suffix} self, size_t size):
        """Set the size of the OldColorList, filling with black if needed."""
        self.colors.resize(size)
        return self

    cpdef OldColorList{suffix} reverse(self):
        """Reverse the colors in place."""
        reverse(self.colors)
        return self

    cpdef OldColorList{suffix} rotate(self, int pos):
        """In-place rotation of the colors forward by `pos` positions."""
        rotate(self.colors, pos)
        return self

    cpdef OldColorList{suffix} sort(self, object key=None, bool reverse=False):
        """Sort items."""
        if key is None:
            sortColors(self.colors)
            if reverse:
                self.reverse()
        else:
            self[:] = sorted(self, key=key, reverse=reverse)
        return self

    # Basic arithmetic operations.
    cpdef OldColorList{suffix} add(OldColorList{suffix} self, c):
        """Add into colors from either a number or a OldColorList."""
        if isinstance(c, Number):
            addInto(<float> c, self.colors)
        else:
            addInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} div(OldColorList{suffix} self, c):
        """Divide colors by either a number or a OldColorList."""
        if isinstance(c, Number):
            divideInto(<float> c, self.colors)
        else:
            divideInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} mul(OldColorList{suffix} self, c):
        """Multiply colors by either a number or a OldColorList."""
        if isinstance(c, Number):
            multiplyInto(<float> c, self.colors)
        else:
            multiplyInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} pow(OldColorList{suffix} self, float c):
        """Raise each color to the given power (gamma correction)."""
        if isinstance(c, Number):
            powInto(<float> c, self.colors)
        else:
            powInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} sub(OldColorList{suffix} self, c):
        """Subtract either a number or a OldColorList from the colors."""
        if isinstance(c, Number):
             subtractInto(<float> c, self.colors)
        else:
             subtractInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    # Arithmetic where "self" is on the right side.
    cpdef OldColorList{suffix} rdiv(OldColorList{suffix} self, c):
        """Right-side divide colors by either a number or a OldColorList."""
        if isinstance(c, Number):
            rdivideInto(<float> c, self.colors)
        else:
            rdivideInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} rpow(OldColorList{suffix} self, c):
        """Right-hand (reversed) call of pow()."""
        if isinstance(c, Number):
            rpowInto(<float> c, self.colors)
        else:
            rpowInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    cpdef OldColorList{suffix} rsub(OldColorList{suffix} self, c):
        """Right-side subtract either a number or a OldColorList."""
        if isinstance(c, Number):
             rsubtractInto(<float> c, self.colors)
        else:
             rsubtractInto((<OldColorList{suffix}> c).colors, self.colors)
        return self

    # Mutators corresponding to built-in operations.
    cpdef OldColorList{suffix} abs(self):
        """Replace each color by its absolute value."""
        absInto(self.colors)
        return self

    cpdef OldColorList{suffix} ceil(self):
        """Replace each color by its integer ceiling."""
        ceilInto(self.colors)
        return self

    cpdef OldColorList{suffix} floor(self):
        """Replace each color by its integer floor."""
        floorInto(self.colors)
        return self

    cpdef OldColorList{suffix} invert(self):
        """Replace each color by its complementary color."""
        invertColor(self.colors)
        return self

    cpdef OldColorList{suffix} neg(self):
        """Negate each color in the list."""
        negateColor(self.colors)
        return self

    cpdef OldColorList{suffix} round(self, uint digits=0):
        """Round each element in each color to the nearest integer."""
        roundColor(self.colors, digits)
        return self

    # Other mutators.
    cpdef OldColorList{suffix} trunc(self):
        """Truncate each value to an integer."""
        truncColor(self.colors)
        return self

    cpdef OldColorList{suffix} hsv_to_rgb(self):
        """Convert each color in the list from HSV to RBG."""
        hsvToRgbInto(self.colors, {base})
        return self

    cpdef OldColorList{suffix} max_limit(self, float max):
        """Limit each color to be not greater than max."""
        if isinstance(max, Number):
            minInto(<float> max, self.colors)
        else:
            minInto((<OldColorList{suffix}> max).colors, self.colors)
        return self

    cpdef OldColorList{suffix} min_limit(self, float min):
        """Limit each color to be not less than min."""
        if isinstance(min, Number):
            maxInto(<float> min, self.colors)
        else:
            maxInto((<OldColorList{suffix}> min).colors, self.colors)
        return self

    cpdef OldColorList{suffix} rgb_to_hsv(self):
        """Convert each color in the list from RBG to HSV."""
        rgbToHsvInto(self.colors, {base})
        return self

    cpdef OldColorList{suffix} zero(self):
        """Set all colors to black."""
        clearInto(self.colors)
        return self

    # Methods that do not change this OldColorList.
    cpdef float distance2(OldColorList{suffix} self, OldColorList{suffix} x):
        """Return the square of the cartestian distance to another OldColorList."""
        return distance2(self.colors, x.colors)

    cpdef float distance(OldColorList{suffix} self, OldColorList{suffix} x):
        """Return the cartestian distance to another OldColorList."""
        return distance(self.colors, x.colors)

    cpdef OldColor{suffix} max(self):
        """Return the maximum values of each component."""
        cdef OldColorS c = maxColor(self.colors)
        return OldColor{suffix}(c.red, c.green, c.blue)

    cpdef OldColor{suffix} min(self):
        """Return the minimum values of each component/"""
        cdef OldColorS c = minColor(self.colors)
        return OldColor{suffix}(c.red, c.green, c.blue)

    @staticmethod
    def spread(*args):
        """Spreads!"""
        cdef OldColorList{suffix} cl = OldColorList{suffix}()
        cdef OldColor{suffix} color
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                color = _toOldColor{suffix}(item)
                spreadAppend(color.color, last_number - 1, cl.colors)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        spread_append(None)
        return cl
