from numbers import Number

cdef class ColorList256:
    """A list of RGB floating point Colors, with many mutating functions.

       A ColorList looks quite like a Python list of Colors (which look like
       tuples) with the big interface difference that operations like + and *
       perform arithmetic and not list construction.

       Written in C++, this class should consume significantly fewer memory and
       CPU resources than a corresponding Python list, as well as providing a
       range of useful facilities.

       While ColorList provides a full set of functions and operations that
       create new ColorLists, in each case there is a corresponding mutating
       function or operation that works "in-place" with no heap allocations
       at all, for best performance.

       The base class ColorList is a list of Color, which are normalized to
       [0, 1]; the derived class ColorList256 is a list of Color256, which
       are normalized to [0, 255].
"""
    cdef ColorVector colors

    # Magic methods.
    def __cinit__(self, items=None):
        """Construct a ColorList with an iterator of items, each of which looks
           like a Color."""
        if items is not None:
            if isinstance(items, ColorList256):
                self.colors = (<ColorList256> items).colors
            else:
                # A list of tuples, Colors or strings.
                self.colors.resize(len(items))
                for i, item in enumerate(items):
                    self[i] = item

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step, index
        cdef float r, g, b
        cdef ColorList256 cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            if isinstance(x, ColorList256):
                cl = <ColorList256> x
            else:
                cl = ColorList256(x)
            if sliceIntoVector(cl.colors, self.colors, begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        index = key
        if not self.colors.fixKey(index):
            raise IndexError('ColorList index out of range ' + str(index))
        try:
            if isinstance(x, str):
                x = Color256(x)
            r, g, b = x
            self.colors.setColor(index, r, g, b)
        except:
            raise ValueError('Can\'t convert ' + str(x) + ' to a color')

    def __getitem__(self, object key):
        cdef ColorS c
        cdef int index
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            cl = ColorList256()
            cl.colors = sliceVector(self.colors, begin, end, step)
            return cl

        index = key
        if not self.colors.fixKey(index):
            raise IndexError('ColorList index out of range ' + str(key))

        c = self.colors[index]
        return Color256(c.red, c.green, c.blue)

    def __add__(ColorList256 self, ColorList256 cl):
        cdef ColorList256 result = ColorList256()
        result.colors = self.colors
        appendInto(cl.colors, result.colors)
        return result

    def __iadd__(ColorList256 self, ColorList256 cl):
        appendInto(cl.colors, self.colors)
        return self

    def __mul__(object self, object other):
        # A little tricky because ColorList can appear on the left or the
        # right side of the argument.
        cdef size_t mult
        cdef ColorList256 cl = ColorList256()
        if isinstance(self, ColorList256):
            cl.colors = (<ColorList256> self).colors
            mult = <size_t> other
        else:
            cl.colors = (<ColorList256> other).colors
            mult = <size_t> self
        duplicateInto(mult, cl.colors)
        return cl

    def __imul__(ColorList256 self, size_t mult):
        duplicateInto(mult, self.colors)
        return self

    def __len__(self):
        return self.colors.size()

    def __repr__(self):
        return 'ColorList256(%s)' % str(self)

    def __richcmp__(ColorList256 self, ColorList256 other, int rcmp):
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    def __sizeof__(ColorList256 self):
        return self.colors.getSizeOf()

    def __str__(ColorList256 self):
        return toString(self.colors).decode('ascii')

    # List operations.
    cpdef ColorList256 append(ColorList256 self, Color256 c):
        """Append to the list of colors."""
        self.colors.push_back(c.color)
        return self

    cpdef ColorList256 clear(self):
        """Resize the list of colors to 0."""
        self.colors.clear()
        return self

    cpdef ColorList256 copy(self):
        """Resize a copy of this list."""
        cdef ColorList256 cl = ColorList256()
        cl.colors = self.colors
        return cl

    cpdef size_t count(self, Color256 color):
        """Return the number of times a color appears in this list."""
        return count(self.colors, color.color)

    cpdef ColorList256 extend(ColorList256 self, object values):
        """Extend the colors from an iterator."""
        appendInto(ColorList256(values).colors, self.colors)
        return self

    cpdef index(ColorList256 self, Color256 color):
        """Returns an index to the first occurance of that Color, or
           raises a ValueError if that Color isn't there."""
        cdef int id = indexOf(self.colors, color.color)
        if id >= 0:
            return id
        raise ValueError('Can\'t find color %s' % color)

    cpdef ColorList256 insert(ColorList256 self, int key,
                                   Color256 color):
        """Insert a color before key."""
        insertBefore(self.colors, key, color.color)
        return self

    cpdef Color256 pop(ColorList256 self, int key = -1):
        """Pop the color at key."""
        cdef Color256 result = Color256()
        if popAt(self.colors, key, result.color):
            return result
        raise IndexError('pop index out of range')

    cpdef ColorList256 remove(self, Color256 color):
        """Find and remove a specific color."""
        self.pop(self.index(color))
        return self

    cpdef ColorList256 resize(ColorList256 self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)
        return self

    cpdef ColorList256 reverse(self):
        """Reverse the colors in place."""
        reverse(self.colors)
        return self

    cpdef ColorList256 rotate(self, int pos):
        """In-place rotation of the colors forward by `pos` positions."""
        rotate(self.colors, pos)
        return self

    cpdef ColorList256 sort(self, object key=None, bool reverse=False):
        """Sort items."""
        if key is None:
            sortColors(self.colors)
            if reverse:
                self.reverse()
        else:
            self[:] = sorted(self, key=key, reverse=reverse)
        return self

    # Basic arithmetic operations.
    cpdef ColorList256 add(ColorList256 self, c):
        """Add into colors from either a number or a ColorList."""
        if isinstance(c, Number):
            addInto(<float> c, self.colors)
        else:
            addInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 div(ColorList256 self, c):
        """Divide colors by either a number or a ColorList."""
        if isinstance(c, Number):
            divideInto(<float> c, self.colors)
        else:
            divideInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 mul(ColorList256 self, c):
        """Multiply colors by either a number or a ColorList."""
        if isinstance(c, Number):
            multiplyInto(<float> c, self.colors)
        else:
            multiplyInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 pow(ColorList256 self, float c):
        """Raise each color to the given power (gamma correction)."""
        if isinstance(c, Number):
            powInto(<float> c, self.colors)
        else:
            powInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 sub(ColorList256 self, c):
        """Subtract either a number or a ColorList from the colors."""
        if isinstance(c, Number):
             subtractInto(<float> c, self.colors)
        else:
             subtractInto((<ColorList256> c).colors, self.colors)
        return self

    # Arithmetic where "self" is on the right side.
    cpdef ColorList256 rdiv(ColorList256 self, c):
        """Right-side divide colors by either a number or a ColorList."""
        if isinstance(c, Number):
            rdivideInto(<float> c, self.colors)
        else:
            rdivideInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 rpow(ColorList256 self, c):
        """Right-hand (reversed) call of pow()."""
        if isinstance(c, Number):
            rpowInto(<float> c, self.colors)
        else:
            rpowInto((<ColorList256> c).colors, self.colors)
        return self

    cpdef ColorList256 rsub(ColorList256 self, c):
        """Right-side subtract either a number or a ColorList."""
        if isinstance(c, Number):
             rsubtractInto(<float> c, self.colors)
        else:
             rsubtractInto((<ColorList256> c).colors, self.colors)
        return self

    # Mutators corresponding to built-in operations.
    cpdef ColorList256 abs(self):
        """Replace each color by its absolute value."""
        absInto(self.colors)
        return self

    cpdef ColorList256 ceil(self):
        """Replace each color by its integer ceiling."""
        ceilInto(self.colors)
        return self

    cpdef ColorList256 floor(self):
        """Replace each color by its integer floor."""
        floorInto(self.colors)
        return self

    cpdef ColorList256 invert(self):
        """Replace each color by its complementary color."""
        invertColor(self.colors)
        return self

    cpdef ColorList256 neg(self):
        """Negate each color in the list."""
        negateColor(self.colors)
        return self

    cpdef ColorList256 round(self, uint digits=0):
        """Round each element in each color to the nearest integer."""
        roundColor(self.colors, digits)
        return self

    # Other mutators.
    cpdef ColorList256 trunc(self):
        """Truncate each value to an integer."""
        truncColor(self.colors)
        return self

    cpdef ColorList256 hsv_to_rgb(self):
        """Convert each color in the list from HSV to RBG."""
        hsvToRgbInto(self.colors, integer)
        return self

    cpdef ColorList256 max_limit(self, float max):
        """Limit each color to be not greater than max."""
        if isinstance(max, Number):
            minInto(<float> max, self.colors)
        else:
            minInto((<ColorList256> max).colors, self.colors)
        return self

    cpdef ColorList256 min_limit(self, float min):
        """Limit each color to be not less than min."""
        if isinstance(min, Number):
            maxInto(<float> min, self.colors)
        else:
            maxInto((<ColorList256> min).colors, self.colors)
        return self

    cpdef ColorList256 rgb_to_hsv(self):
        """Convert each color in the list from RBG to HSV."""
        rgbToHsvInto(self.colors, integer)
        return self

    cpdef ColorList256 zero(self):
        """Set all colors to black."""
        clearInto(self.colors)
        return self

    # Methods that do not change this ColorList.
    cpdef float distance2(ColorList256 self, ColorList256 x):
        """Return the square of the cartestian distance to another ColorList."""
        return distance2(self.colors, x.colors)

    cpdef float distance(ColorList256 self, ColorList256 x):
        """Return the cartestian distance to another ColorList."""
        return distance(self.colors, x.colors)

    cpdef Color256 max(self):
        """Return the maximum values of each component."""
        cdef ColorS c = maxColor(self.colors)
        return Color256(c.red, c.green, c.blue)

    cpdef Color256 min(self):
        """Return the minimum values of each component/"""
        cdef ColorS c = minColor(self.colors)
        return Color256(c.red, c.green, c.blue)

    @staticmethod
    def spread(*args):
        """Spreads!"""
        cdef ColorList256 cl = ColorList256()
        cdef Color256 color
        cdef size_t last_number = 0

        def spread_append(item):
            nonlocal last_number
            if last_number:
                color = _toColor256(item)
                spreadAppend(cl.colors, last_number - 1, color.color)
                last_number = 0

        for a in args:
            if isinstance(a, Number):
                last_number += a
            else:
                last_number += 1
                spread_append(a)

        spread_append(None)
        return cl