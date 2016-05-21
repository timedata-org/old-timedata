import unittest

from tdsp import Color, ColorList

class TestColorList(unittest.TestCase):
    def test_trivial(self):
        cl = ColorList()
        self.assertEqual(len(cl), 0)
        cl.reverse()
        self.assertEqual(len(cl), 0)

    def test_construct(self):
        cl = ColorList([[1, 1, 1]])
        self.assertEqual(str(cl), str(ColorList(['white'])))
        self.assertEqual(cl, ColorList(['white']))

    def test_arithmetic(self):
        cl = ColorList(('red', 'green', 'blue'))
        self.assertEqual(cl + cl, cl * 2)
        # self.assertEqual(2 + (2 * cl * 3) + 2 - 2 * cl, 4 + 4 * cl)

    def test_slicing(self):
        cl = ColorList()
        cl[:] = 'red', 'green', 'blue'
        self.assertEqual(cl, ColorList(['red', 'green', 'blue']))
        self.assertEqual(cl[1:2], ColorList(['green']))

    def test_rotate(self):
        cl = ColorList(('red', 'green', 'blue'))
        cl.rotate(1)
        self.assertEqual(cl, ColorList(['green', 'blue', 'red']))

    def test_extend(self):
        cl = ColorList()
        cl.extend(('red', 'green', 'blue'))
        self.assertEqual(cl, ColorList(['red', 'green', 'blue']))
        try:
            cl.extend(1)
        except:
            pass
        else:
            self.assertTrue(False)
        self.assertEqual(cl, ColorList(['red', 'green', 'blue']))


    def test_indexing(self):
        red, green, blue = (
            Color('red'), Color('green'), Color('blue'))
        c = ColorList((red, green, blue))
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
        cl = ColorList()
        cl.append('red')
        cl.append((1, 1, 1))
        self.assertEqual(cl, ColorList(('red', 'white')))

    def test_div_pow(self):
        c = ColorList(('red', 'green', 'blue'))
        c[1] = -c[1]
        cl = c / 0
        self.assertEqual(cl[0][0], float('inf'))
        self.assertFalse(cl[0][1] == cl[0][1])
        self.assertEqual(cl[1][1], float('-inf'))

        self.assertEqual(0 ** c, ColorList(('cyan', 'magenta', 'yellow')))
