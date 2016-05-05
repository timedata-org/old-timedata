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
