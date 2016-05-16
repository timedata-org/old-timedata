import unittest

from tdsp import Color, CColorList

class TestCColorList(unittest.TestCase):
    def test_trivial(self):
        cl = CColorList()
        self.assertEqual(len(cl), 0)
        cl.reverse()
        self.assertEqual(len(cl), 0)

    def test_construct(self):
        cl = CColorList([[1, 1, 1]])
        self.assertEqual(str(cl), str(CColorList(['white'])))
        self.assertEqual(cl, CColorList(['white']))

    def test_arithmetic(self):
        cl = CColorList(('red', 'green', 'blue'))
        self.assertEqual(cl + cl, cl * 2)
        # self.assertEqual(2 + (2 * cl * 3) + 2 - 2 * cl, 4 + 4 * cl)

    def test_slicing(self):
        cl = CColorList()
        cl[:] = 'red', 'green', 'blue'
        self.assertEqual(cl, CColorList(['red', 'green', 'blue']))
        self.assertEqual(cl[1:2], CColorList(['green']))

    def test_rotate(self):
        cl = CColorList(('red', 'green', 'blue'))
        cl.rotate(1)
        self.assertEqual(cl, CColorList(['green', 'blue', 'red']))

    def test_indexing(self):
        red, green, blue = (
            Color('red'), Color('green'), Color('blue'))
        c = CColorList((red, green, blue))
        self.assertEqual(c[0], red)
        self.assertEqual(c[1], green)
        self.assertEqual(c[2], blue)
        self.assertEqual(c[-3], red)
        self.assertEqual(c[-2], green)
        self.assertEqual(c[-1], blue)
        with self.assertRaises(IndexError):
            c[-4]
        with self.assertRaises(IndexError):
            c[3]

        r, g, b = c
        self.assertEqual(r, red)
        self.assertEqual(g, green)
        self.assertEqual(b, blue)

    def test_append(self):
        cl = CColorList()
        cl.append('red')
        cl.append((1, 1, 1))
        self.assertEqual(cl, CColorList(('red', 'white')))
