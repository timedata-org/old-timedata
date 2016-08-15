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
        black += 1
        black *= 2
        black /= 2
        self.assertEqual(tuple(black), (1, 1, 1))
