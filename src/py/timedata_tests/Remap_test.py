import unittest

from timedata import *

Colors = Color.by_name

class TestRemap(unittest.TestCase):
    def check_identity(self, remap, *colors, result=None):
        cl = ColorList(colors)
        result = ColorList(cl if result is None else result)

        self.assertEqual(remap.map(cl[:]), result)
        self.assertEqual(cl[:].remap(remap), result)

        copy = cl[:]

        self.assertEqual(cl[:].remap_to(remap, copy), result)
        self.assertEqual(remap.map_to(cl[:], copy), result)
        self.assertEqual(copy, result)

        copy = cl[:]
        self.assertEqual(copy.remap_into(remap), result)
        self.assertEqual(copy, result)

    def test_empty(self):
        self.check_identity(Remap())

    def test_trivial(self):
        self.check_identity(Remap(range(3)), 'red', 'green', 'blue')

    def test_reverse(self):
        self.check_identity(Remap(list(reversed(range(3)))),
                            'red', 'green', 'blue',
                            result=('blue', 'green', 'red'))
