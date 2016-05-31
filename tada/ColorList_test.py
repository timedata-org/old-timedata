import unittest

from tada import Color, Colors, ColorList

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
        self.assertEqual(cl.copy().add(cl), cl.copy().mul(2))
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

    def test_append(self):
        cl = ColorList()
        cl.append('red')
        self.assertEqual(cl, ColorList(('red')))

        cl.append('green')
        self.assertEqual(cl, ColorList(('red', 'green')))

        with self.assertRaises(ValueError):
            cl.append('wombat')
        self.assertEqual(cl, ColorList(('red', 'green')))

    def test_clear(self):
        self.assertEqual(ColorList(('red', 'green')).clear(),
                         ColorList())
        self.assertEqual(ColorList(('red', 'green')).zero(),
                         ColorList(('black', 'black')))

    def test_mult(self):
        cl = ColorList(('red', 'green', 'blue'))
        cl2 = ColorList(('red', 'green', 'blue', 'red', 'green', 'blue',
                        'red', 'green', 'blue'))
        self.assertEqual(cl * 3, cl2)
        self.assertEqual(3 * cl, cl2)
        self.assertEqual(cl * 1, cl)
        self.assertEqual(1 * cl, cl)
        self.assertEqual(cl * 0, ColorList())
        self.assertEqual(0 * cl, ColorList())

        cl *= 3
        self.assertEqual(cl, cl2)
        cl *= 1
        self.assertEqual(cl, cl2)
        cl *= 0
        self.assertEqual(cl, ColorList())

        cl = ColorList(('red', 'green', 'blue'))
        with self.assertRaises(OverflowError):
            cl *= -1
        with self.assertRaises(OverflowError):
            cl * -1
        self.assertEqual(cl, ColorList(('red', 'green', 'blue')))

    def test_add(self):
        cl = ColorList(['red', 'green', 'blue'])
        cl += ColorList(['yellow', 'black'])
        self.assertEqual(cl, ColorList(
            ['red', 'green', 'blue', 'yellow', 'black']))
        self.assertEqual(cl, cl + ColorList())
        self.assertEqual(cl, ColorList() + cl)

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
        cl.append(Colors.red)
        cl.append(Color(1, 1, 1))
        self.assertEqual(cl, ColorList(('red', 'white')))

    def test_div_pow(self):
        c = ColorList(('red', 'green', 'blue'))
        c[1] = -c[1]
        cl = c.copy().div(0)
        self.assertEqual(cl[0][0], float('inf'))
        self.assertFalse(cl[0][1] == cl[0][1])
        self.assertEqual(cl[1][1], float('-inf'))

        self.assertEqual(c.rpow(0), ColorList(('cyan', 'magenta', 'yellow')))

    def test_max_min(self):
        self.assertEqual(ColorList().max(), Colors.black)
        self.assertEqual(ColorList().min(), Colors.black)

        c = ColorList(('red', 'green', 'blue'))
        self.assertEqual(c.max(), Colors.white)
        self.assertEqual(c.min(), Colors.black)

        c.min_limit(0.25).max_limit(0.75)

        gray = Colors.white * 0.25
        self.assertEqual(c, ColorList((gray + Colors.red / 2,
                                       gray + Colors.green / 2,
                                       gray + Colors.blue / 2)))

    def test_round(self):
        cl = ColorList(((0.15, 0.24, 0.36), (-0.15, -0.24, -0.36)))
        self.assertEqual(cl.round(1),
                             ColorList(((0.2, 0.2, 0.4), (-0.2, -0.2, -0.4))))

    def test_distance(self):
        cl = ColorList()
        self.assertEqual(cl.distance(ColorList()), 0)
        self.assertEqual(cl.distance2(ColorList()), 0)

        self.assertEqual(cl.distance(ColorList(['black'])), 0)
        self.assertEqual(cl.distance2(ColorList(['black'])), 0)

        self.assertEqual(cl.distance2(ColorList(['white'])), 3)

    def test_list_ops(self):
        cl = ColorList(('red', 'green', 'blue'))
        cl2 = cl.copy()
        self.assertEqual(cl, cl2)
        self.assertIsNot(cl, cl2)
        self.assertEqual(cl.count(Colors.red), 1)
        self.assertEqual(cl.count(Colors.yellow), 0)
        self.assertEqual(cl.index(Colors.blue), 2)
        with self.assertRaises(ValueError):
            cl.index(Colors.white)

    def test_insert(self):
        cl = ColorList(('red', 'green', 'blue'))
        self.assertEqual(cl.copy().insert(0, Colors.white),
                         ColorList(('white', 'red', 'green', 'blue')))
        self.assertEqual(cl.copy().insert(1, Colors.white),
                         ColorList(('red', 'white', 'green', 'blue')))
        self.assertEqual(cl.copy().insert(2, Colors.white),
                         ColorList(('red', 'green', 'white', 'blue')))
        self.assertEqual(cl.copy().insert(3, Colors.white),
                         ColorList(('red', 'green', 'blue', 'white')))

        self.assertEqual(cl.copy().insert(-1, Colors.white),
                         ColorList(('red', 'green', 'white', 'blue')))
        self.assertEqual(cl.copy().insert(-2, Colors.white),
                         ColorList(('red', 'white', 'green', 'blue')))
        self.assertEqual(cl.copy().insert(-3, Colors.white),
                         ColorList(('white', 'red', 'green', 'blue')))

        self.assertEqual(cl.copy().insert(-4, Colors.white),
                         ColorList(('white', 'red', 'green', 'blue')))
        self.assertEqual(cl.copy().insert(-5, Colors.white),
                         ColorList(('white', 'red', 'green', 'blue')))

    def test_pop(self):
        cl = ColorList(('red', 'green', 'blue'))
        cl2 = cl.copy()
        self.assertEqual(cl2.pop(), Colors.blue)
        self.assertEqual(cl2, cl[:2])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(-1), Colors.blue)
        self.assertEqual(cl2, cl[:2])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(0), Colors.red)
        self.assertEqual(cl2, cl[1:])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(-3), Colors.red)
        self.assertEqual(cl2, cl[1:])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(1), Colors.green)
        self.assertEqual(cl2, cl[0:3:2])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(-2), Colors.green)
        self.assertEqual(cl2, cl[0:3:2])

        cl2 = cl.copy()
        self.assertEqual(cl2.pop(2), Colors.blue)
        self.assertEqual(cl2, cl[:2])

        with self.assertRaises(IndexError):
            cl.copy().pop(3)
        with self.assertRaises(IndexError):
            cl.copy().pop(4)
        with self.assertRaises(IndexError):
            cl.copy().pop(-4)
        with self.assertRaises(IndexError):
            cl.copy().pop(-5)

    def test_remove(self):
        cl = ColorList(('green', 'blue', 'red'))
        cl2 = cl.copy()
        self.assertEqual(cl2.remove(Colors.red), cl[:-1])
        cl2 = cl.copy()
        self.assertEqual(cl2.remove(Colors.green), cl[1:])
        with self.assertRaises(ValueError):
            cl.copy().remove(Colors.white)

    def test_sort(self):
        cl = ColorList(('red', 'green', 'blue'))
        self.assertEqual(cl.copy().sort(reverse=True), cl)
        self.assertEqual(cl.copy().sort(), cl[::-1])
