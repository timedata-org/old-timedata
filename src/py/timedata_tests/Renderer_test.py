import unittest

from timedata import *

COLORS = ColorListRGB(['red', 'green', 'blue'])
HALF_COLORS = COLORS.copy().mul(0.5)

def render(colors=COLORS, **kwds):
    return list(Renderer(**kwds).render(colors))


class TestRenderer(unittest.TestCase):
    def test_half(self):
        self.assertEqual(render(HALF_COLORS), [128, 0, 0, 0, 128, 0, 0, 0, 128])

    def test_trivial(self):
        self.assertTrue(not render(ColorListRGB()))

    def test_simple(self):
        self.assertEqual(render(), [255, 0, 0, 0, 255, 0, 0, 0, 255])

    def test_perm(self):
        self.assertEqual(render(permutation='grb'),
                         [0, 255, 0, 255, 0, 0, 0, 0, 255])

    def test_trivial_gamma(self):
        self.assertEqual(render(gamma=2.5),
                         [255, 0, 0, 0, 255, 0, 0, 0, 255])

    def test_half_gamma(self):
        r = render(HALF_COLORS, gamma=2.5)
        self.assertEqual(r, [45, 0, 0, 0, 45, 0, 0, 0, 45])
        self.assertEqual(r, render(COLORS, gamma=2.5, level=0.5))

    def test_gamma_90(self):
        r = render(COLORS.copy().mul(0.9), gamma=2.5)
        self.assertEqual(r, [196, 0, 0, 0, 196, 0, 0, 0, 196])
        self.assertEqual(r, render(COLORS, gamma=2.5, level=0.9))
