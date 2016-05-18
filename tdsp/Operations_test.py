import unittest

from tdsp import *

class TestOperations(unittest.TestCase):
    def test_spread(self):
        cl = ColorList.spread(Color('white'), Color('black'), 0)
        self.assertEqual(cl, ColorList())

        cl = ColorList.spread(Color('white'), Color('black'), 1)
        self.assertEqual(cl, ColorList(['white']))

        cl = ColorList.spread(Color('white'), Color('black'), 2)
        self.assertEqual(cl, ColorList(['white', 'black']))

        cl = ColorList.spread(Color('white'), Color('black'), 3)
        self.assertEqual(cl, ColorList(['white', 'gray 50', 'black']))

        cl = ColorList.spread(Color('red'), Color('blue'), 3)
        self.assertEqual(cl, ColorList(('red', (0.5, 0, 0.5), 'blue')))
