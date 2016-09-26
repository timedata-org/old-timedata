import pickle, unittest

from timedata import *

Colors = Color.by_name

class TestIndexList(unittest.TestCase):
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
        self.check_identity(IndexList())

    def test_trivial(self):
        self.check_identity(IndexList(range(3)), 'red', 'green', 'blue')

    def test_reverse(self):
        self.check_identity(IndexList(list(reversed(range(3)))),
                            'red', 'green', 'blue',
                            result=('blue', 'green', 'red'))

    def test_out_of_range(self):
        with self.assertRaises(IndexError):
            ColorList().remap(IndexList(range(1)))

        with self.assertRaises(IndexError):
            ColorList(['red']).remap(IndexList([1]))

        ColorList(['red']).remap(IndexList([-1]))
        with self.assertRaises(IndexError):
            ColorList(['red']).remap(IndexList([-2]))

    def test_pickle(self):
        for i in range(0), range(1), range(11):
            c = IndexList(i)
            self.assertEqual(pickle.loads(pickle.dumps(c)), c)

    def test_shuffle(self):
        c = list(IndexList(range(1000)).shuffle())

        # One chance in about 10**5912 that this will fail.  :-D
        self.assertNotEqual(c, list(range(1000)))
        self.assertEqual(list(sorted(c)), list(range(1000)))
