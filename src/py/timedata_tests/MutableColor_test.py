import unittest

from timedata import *

class TestMutable(unittest.TestCase):
    def test_white(self):
        white = MutableColor('white')
        self.assertEqual(tuple(white), (1, 1, 1))

        white.red = 0
        white.green = 0
        self.assertEqual(white, Color.by_name.blue)

    def test_ops(self):
        black = MutableColor()
        black.add_into(1)
        black.mul_into(2)
        black.div_into(2)
        self.assertEqual(tuple(black), (1, 1, 1))

    def test_list(self):
        colors = ColorList(['red', 'green', 'blue'])

        r = colors.get(0)
        self.assertEqual(r, Color.by_name.red)

        s = colors.get(1, r)
        self.assertEqual(s, Color.by_name.green)
        self.assertEqual(r, Color.by_name.green)
