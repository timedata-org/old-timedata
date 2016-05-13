import unittest

from tdsp import ColorList

class TestColorList(unittest.TestCase):
    def test_trivial(self):
        cl = ColorList()
        self.assertEqual(len(cl), 0)
        cl.reverse()
        self.assertEqual(len(cl), 0)

    def test_construct(self):
        cl = ColorList([1, 1, 1])
        self.assertEqual(str(cl), str(ColorList(['white'])))
        self.assertEqual(cl, ColorList(['white']))

    def test_slicing(self):
        cl = ColorList()
        cl[:] = 'red', 'green', 'blue'
        self.assertEqual(cl, ColorList(['red', 'green', 'blue']))
