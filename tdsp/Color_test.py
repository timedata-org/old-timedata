import unittest

from tdsp import Color, Color256

class TestColor(object): # (unittest.TestCase):
    def test_white(self):
        white = Color((1, 1, 1))
        self.assertEqual(str(white), 'white')
        self.assertEqual(white[:], white)
        self.assertEqual(white[::-1], white)
        self.assertEqual(white[0:2], (1.0, 1.0))

    def test_red(self):
        red = Color((1, 0, 0))
        blue = Color('blue')

        self.assertEqual(str(red), 'red')
        self.assertEqual(red[:], red)
        self.assertEqual(red[::-1], blue)
        self.assertEqual(red[-3:3:1], red)
        self.assertEqual(red[-1:-3:-1], (0.0, 0.0))
        self.assertEqual(red[-3:-1], (1.0, 0.0))
        self.assertEqual(red[0:2], (1.0, 0.0))

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


class TestColor256(unittest.TestCase):
    def test_first(self):
        white = Color256((255, 255, 255))
        self.assertEqual(str(white), 'white')
        self.assertEqual(white[:], white)
        self.assertEqual(white[::-1], white)
        self.assertEqual(white[0:2], (255, 255))

    def test_red(self):
        red = Color256((255, 0, 0))
        blue = Color256('blue')

        self.assertEqual(str(red), 'red')
        self.assertEqual(red[:], red)
        self.assertEqual(red[-1:-3:-1], (0.0, 0.0))
        self.assertEqual(red[-3:-1], (255, 0.0))
        self.assertEqual(red[0:2], (255, 0.0))
        self.assertEqual(red[-3:3:1], red)
        self.assertEqual(red[::-1], blue)

    def test_arithmetic(self):
        black, red, green, blue, white, yellow, cyan, magenta = (
            Color256(i) for i in ('black', 'red', 'green', 'blue', 'white',
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

        self.assertEqual(white * red / 255, red)
        self.assertEqual(white * cyan / 255, cyan)
