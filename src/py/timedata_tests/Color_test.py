import unittest

from timedata import *

HSV = color.hsv.Color
Colors = Color.by_name
HSVColors = HSV.by_name

class TestColor(unittest.TestCase):
    def test_white(self):
        white = Color(1, 1, 1)
        self.assertEqual(str(white), 'white')
        self.assertEqual(white, Color((1, 1, 1)))
        self.assertEqual(white[:], white)
        self.assertEqual(white[::-1], white)
        self.assertEqual(white[0:2], (1.0, 1.0))

    def test_red(self):
        red = Color(1, 0, 0)
        blue = Color('blue')

        self.assertEqual(str(red), 'red')
        self.assertEqual(red[:], red)
        self.assertEqual(red[::-1], blue)
        self.assertEqual(red[-3:3:1], red)
        self.assertEqual(red[-1:-3:-1], (0.0, 0.0))
        self.assertEqual(red[-3:-1], (1.0, 0.0))
        self.assertEqual(red[0:2], (1.0, 0.0))

    def test_mixed(self):
        antired = Color(-1, 0, 0)
        self.assertEqual(str(antired), 'red-++')
        self.assertEqual(antired + Color('red'), Color('black'))
        self.assertEqual(str(-Color('white')), 'white---')

    def test_arithmetic(self):
        black, red, green, blue, white, yellow, cyan, magenta = (
            Color(i) for i in ('black', 'red', 'green', 'blue', 'white',
                               'yellow', 'cyan', 'magenta'))

        self.assertEqual(red + green + blue, white)
        self.assertEqual(red + green, yellow)
        self.assertEqual(green + blue, cyan)
        self.assertEqual(red + blue, magenta)

        self.assertEqual(white - blue, yellow)
        self.assertEqual(white - green, magenta)
        self.assertEqual(white - red, cyan)

        self.assertEqual(~white, black)
        self.assertEqual(~black, white)

        self.assertEqual(white * red, red)
        self.assertEqual(white * cyan, cyan)

    def test_methods(self):
        self.assertEqual(Color().START, 0)
        self.assertEqual(Color().RANGE, 1.0)

    def test_rotated(self):
        self.assertEqual(Color('red').rotated(1), Color('blue'))
        g1 = (Color('red') + Color('blue') * 0.5).rotated(-1)
        g2 = Color('green') + Color('red') * 0.5
        # TODO:  but these should be *exactly equal!  Why do I need that?
        self.assertLessEqual(g1.distance(g2), 1.0E-6)

    def test_compare(self):
        for x in 0, -1, 'red', (0.1, 0.1, 0.1):
            x = Color(x)
            self.assertTrue(x == x)
            self.assertFalse(x != x)
            self.assertTrue(x <= x)
            self.assertFalse(x < x)
            self.assertTrue(x >= x)
            self.assertFalse(x > x)

        black, red, green, blue, white, yellow, cyan, magenta = (
            Color(i) for i in ('black', 'red', 'green', 'blue', 'white',
                               'yellow', 'cyan', 'magenta'))
        for x, y in ((red, green), (green, blue), (red + green, red + blue),
                     (white, red), (white, green), (white, blue)):
            self.assertFalse(x == y)
            self.assertTrue(x != y)
            self.assertFalse(x <= y)
            self.assertFalse(x < y)
            self.assertTrue(x >= y)
            self.assertTrue(x > y)

    def test_indexing(self):
        c = Color(1, 2, 3)
        self.assertEqual(c[0], 1)
        self.assertEqual(c[1], 2)
        self.assertEqual(c[2], 3)
        self.assertEqual(c[-3], 1)
        self.assertEqual(c[-2], 2)
        self.assertEqual(c[-1], 3)
        with self.assertRaises(IndexError):
            c[-4]
        with self.assertRaises(IndexError):
            c[3]

        r, g, b = c
        self.assertEqual(c, Color(r, g, b))
        self.assertEqual(c, Color(c))
        self.assertEqual(c, Color(*c))

    def test_abs(self):
        red, green, gray = (
            Color('red'), Color('green'), Color('gray'))
        self.assertEqual(abs(-red), red)
        self.assertEqual(abs(-(red + gray + gray)), red + gray + gray)

    def test_copy(self):
        import copy
        red = Color.by_name.red
        self.assertEqual(red, red.copy())
        self.assertEqual(red, copy.copy(red))
        self.assertEqual(red, copy.deepcopy(red))

    def test_hex(self):
        for k, v in Colors.__dict__.items():
            if not (k.startswith('_') or k.startswith('grey') or
                    k.startswith('gray')):
                h_value = v.to_hex()
                self.assertEqual(Color.from_hex(h_value), Color(v))

    def test_distance(self):
        self.assertEqual(Colors.red.distance2(Colors.green), 2)
        self.assertEqual(Colors.red.distance(Colors.black), 1)

    def test_size(self):
        import sys
        self.assertEqual(sys.getsizeof(Colors.red), 12)

    def test_named_components(self):
        self.assertEqual(Colors.red.red, 1)
        self.assertEqual(Colors.red.green, 0)
        self.assertEqual(Colors.red.blue, 0)

    def DONT_test_everything(self):
        # This test takes about five minutes to run when it's enabled.
        for i in range(256 * 256 * 256):
            if not i % (256 * 256 * 4):
                print('!', end='', flush=True)
            c = Color.from_hex(i)
            self.assertEqual(i, c.to_hex(), i)
            s = str(c)
            c2 = Color(s)
            distance = c.distance(c2)
            self.assertTrue(distance < 0.000001, i)
            self.assertEqual(str(c2), s, i)


class TestColorHSV(unittest.TestCase):
    def test_basics(self):
        for c in 'red', 'orange', 'yellow', 'green', 'black':
            self.assertEqual(str(ColorHSV(c)), c)
            self.assertEqual(str(Color(ColorHSV(c))), c)
        red = ColorHSV.by_name.red
        self.assertEqual(red.hue, 0)
        self.assertEqual(red.saturation, 1)
        self.assertEqual(red.value, 1)
