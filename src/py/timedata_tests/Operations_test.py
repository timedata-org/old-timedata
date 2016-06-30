import unittest

from timedata import *

ColorList = NewColorList
Colors = NewColors

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
        r, g = Colors.red, Colors.green
        self.assertSpread(
            [r, 2, 6, g],
            [r,
             r + 1 * (g - r) / 9,
             r + 2 * (g - r) / 9,
             r + 3 * (g - r) / 9,
             r + 4 * (g - r) / 9,
             r + 5 * (g - r) / 9,
             r + 6 * (g - r) / 9,
             r + 7 * (g - r) / 9,
             r + 8 * (g - r) / 9,
             g])
