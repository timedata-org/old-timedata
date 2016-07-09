import unittest

from timedata import *

try:
    c255 = color.rgb.c255
    c256 = color.rgb.c256

except:
    print()
    print('(skipping ColorRange_test.py)')
    print()

else:
    class TestColorRange(unittest.TestCase):
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
            self.assertEqual(len(c256.Color.names), 481)
            self.assertEqual(c256.Color.names[:10], (
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

        def test_conversions(self):
            for name in Color.names:
                name = str(Color(name))  # Get the canonical name.
                self.assertEqual(str(c256.Color(c255.Color(Color(name)))), name)

        def test_list_conversions(self):
            cl = ColorList(('red', 'green', 'blue'))
            self.assertEqual(str(cl), str(c255.ColorList(cl)))
            self.assertEqual(str(cl), str(c256.ColorList(cl)))
            x = cl
            for c in c255.ColorList, c256.ColorList, ColorList:
                x = c(x)
            self.assertEqual(x.distance(cl), 0)
            self.assertEqual(x, cl)
