import unittest

from tada import Stripe, Combiner, Render3

class TestGenerated(unittest.TestCase):
    def test_stripe(self):
        s = Stripe()
        self.assertEqual(str(s), '(begin=0, skip=1, repeats=1, reflect=False)')
        self.assertEqual(
            repr(s), 'tada.Stripe(begin=0, skip=1, repeats=1, reflect=False)')

        s.skip = 2
        s.reflect = True
        self.assertEqual(str(s), '(begin=0, skip=2, repeats=1, reflect=True)')

    def test_render(self):
        s = Render3()
        self.assertEqual(str(s), '(min=0.0, max=255.0, scale=1.0, gamma=1.0, '
                         'permutation=\'rgb\', offset=0, size=0)')
