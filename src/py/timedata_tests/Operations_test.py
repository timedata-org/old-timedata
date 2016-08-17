import unittest

from timedata import *

class TestOperations(unittest.TestCase):
    def assertSpread(self, args, expect):
        expected = ColorList(expect)
        actual = ColorList.spread(*args)
        failures = []
        if len(expected) != len(actual):
            failures.append('size: %s %s' % (len(expected), len(actual)))
        for i, (e, a) in enumerate(zip(expected, actual)):
            if e.distance2(a) > 0.0001:
                failures.append('color: %s %s %s' % (i, e, a))
        if failures:
            msg = '\n'.join(['Failure', str(args), str(expect), str(actual)]
                             + failures)
            self.fail(msg)


    def test_trivial_spread(self):
        self.assertSpread([], [])
        self.assertSpread(['white'], ['white'])
        self.assertSpread(['white', 'black'], ['white', 'black'])
        self.assertSpread(['white', 0, 'black'], ['white', 'black'])
        self.assertSpread(['white', 1, 'black'], ['white', 'gray 50', 'black'])
        self.assertSpread(['white', 3, 'black'],
                          ['white', 'gray 75', 'gray 50', 'gray 25', 'black'])

    def test_spread(self):
        r, g = Color.by_name.red, Color.by_name.green
        self.assertSpread(
            [r, 2, 6, g],
            [r,
             r.add(g.sub(r).div(9).mul(1)),
             r.add(g.sub(r).div(9).mul(2)),
             r.add(g.sub(r).div(9).mul(3)),
             r.add(g.sub(r).div(9).mul(4)),
             r.add(g.sub(r).div(9).mul(5)),
             r.add(g.sub(r).div(9).mul(6)),
             r.add(g.sub(r).div(9).mul(7)),
             r.add(g.sub(r).div(9).mul(8)),
             g])
