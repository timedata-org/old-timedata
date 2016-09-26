import copy, pickle, unittest

from timedata import Render3

class TestGenerated(unittest.TestCase):
    def test_render3(self):
        r = Render3()
        s = ("(gamma=1.0, min=0, max=255, offset=0.0, permutation='rgb', "
             "prefix=0)")

        self.assertEqual(str(r), s)
        self.assertEqual(repr(r), 'timedata.Render3' + s)

        r.gamma = 2.5
        r.permutation = 'grb'
        s = ("(gamma=2.5, min=0, max=255, offset=0.0, permutation='grb', "
                 "prefix=0)")
        self.assertEqual(str(r), s)
        self.assertEqual(repr(r), 'timedata.Render3' + s)

        r.permutation = 0
        self.assertEqual(r.permutation, 'rgb')
        r.permutation = 1
        self.assertEqual(r.permutation, 'rbg')
        r.permutation = 5
        self.assertEqual(r.permutation, 'bgr')

    def test_raises(self):
        r = Render3()
        with self.assertRaises(ValueError):
            r.permutation = 'rrr'

        with self.assertRaises(ValueError):
            r.permutation = -1

        with self.assertRaises(ValueError):
            r.permutation = 6

    def test_copy(self):
        r = Render3()
        shallow, deep = copy.copy(r), copy.deepcopy(r)
        self.assertEqual(r.gamma, shallow.gamma)
        self.assertEqual(r.gamma, deep.gamma)
        self.assertEqual(shallow.gamma, deep.gamma)

        shallow.gamma = deep.gamma = 2.5
        self.assertNotEqual(r.gamma, shallow.gamma)
        self.assertNotEqual(r.gamma, deep.gamma)
        self.assertEqual(shallow.gamma, deep.gamma)

        shallow.gamma = 1.5
        self.assertNotEqual(shallow.gamma, deep.gamma)

    def test_pickle(self):
        r = Render3(gamma=2.5, permutation='rbg')
        self.assertEqual(str(r), str(r))
        self.assertNotEqual(str(r), str(Render3()))
        self.assertEqual(str(r), str(pickle.loads(pickle.dumps(r))))
