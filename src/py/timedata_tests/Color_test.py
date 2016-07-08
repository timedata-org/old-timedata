import unittest

from timedata import *

c255 = color.rgb.c255
c256 = color.rgb.c256
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

    def test_hex(self):
        for k, v in Colors.__dict__.items():
            if not (k.startswith('_') or k.startswith('grey') or
                    k.startswith('gray')):
                h_value = v.to_hex()
                self.assertEqual(Color.from_hex(h_value), Color(v))

    def test_distance(self):
        self.assertEqual(Colors.red.distance2(Colors.green), 2)
        self.assertEqual(Colors.red.distance(Colors.black), 1)

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


class TestColor256(unittest.TestCase):
    def test_first(self):
        white = c256.Color(256, 256, 256)
        self.assertEqual(str(white), 'white')
        self.assertEqual(white[:], white)
        self.assertEqual(white[::-1], white)
        self.assertEqual(white[0:2], (256, 256))

    def test_string(self):
        self.assertEqual(list(c256.Color('white')), [256, 256, 256])
        self.assertEqual(repr(c256.Color(512, 512, 512)),
                         'ColorRGB256(512, 512, 512)')
        self.assertEqual(repr(c255.Color(255, 510, 765)),
                         'ColorRGB255(255, 510, 765)')

    def test_red(self):
        red = c256.Color((256, 0, 0))
        blue = c256.Color('blue')

        self.assertEqual(str(red), 'red')
        self.assertEqual(red[:], red)
        self.assertEqual(red[-1:-3:-1], (0.0, 0.0))
        self.assertEqual(red[-3:-1], (256, 0.0))
        self.assertEqual(red[0:2], (256, 0.0))
        self.assertEqual(red[-3:3:1], red)
        self.assertEqual(red[::-1], blue)

    def test_arithmetic(self):
        black, red, green, blue, white, yellow, cyan, magenta = (
            c256.Color(i) for i in ('black', 'red', 'green', 'blue', 'white',
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

        self.assertEqual(white * red / 256, red)
        self.assertEqual(white * cyan / 256, cyan)

    def test_methods(self):
        a = (c256.Color('red') + c256.Color('blue') * 0.5).rotated(-1)
        b = c256.Color('green') + c256.Color('red') * 0.5
        self.assertTrue(a.distance(b) < 0.0001)
        self.assertEqual(c256.Color('red').rotated(1), c256.Color('blue'))
        self.assertEqual(c256.Color().RANGE, 256.0)

    def test_names(self):
        self.assertEqual(len(Color.names), 481)
        self.assertEqual(Color.names[:10], (
            'alice blue',
            'antique white',
            'antique white 1',
            'antique white 2',
            'antique white 3',
            'antique white 4',
            'aqua',
            'aquamarine',
            'aquamarine 1',
            'aquamarine 2'))

    def test_limit(self):
        self.assertEqual((Colors.red * 2).limit_max(0), Colors.black)
        self.assertEqual((Colors.red * 2).limit_min(0), Colors.red * 2)
        self.assertEqual((Colors.red * 2).limit_max(1), Colors.red)
        self.assertEqual(tuple((Colors.red * 2).limit_min(1)), (2, 1, 1))
        self.assertEqual(Color(1, 2, 3).limit_max(Color(3, 2, 1)),
                         Color(1, 2, 1))
        self.assertEqual(Color(1, 2, 3).limit_min(Color(3, 2, 1)),
                         Color(3, 2, 3))

    def test_conversions(self):
        for name in Color.names:
            name = str(Color(name))  # Get the canonical name.
            self.assertEqual(str(c256.Color(c255.Color(Color(name)))), name)

class TestColorHSV(unittest.TestCase):
    def test_basics(self):
        for c in 'red', 'orange', 'yellow', 'green', 'black':
            self.assertEqual(str(HSV(c)), c)
            self.assertEqual(str(Color(HSV(c))), c)
