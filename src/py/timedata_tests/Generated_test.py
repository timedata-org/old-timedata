import unittest

from timedata import Stripe, Combiner

class TestGenerated(unittest.TestCase):
    def test_stripe(self):
        s = Stripe()
        self.assertEqual(str(s), '(begin=0, skip=1, repeats=1, reflect=False)')
        self.assertEqual(
            repr(s), 'timedata.Stripe(begin=0, skip=1, repeats=1, reflect=False)')

        s.skip = 2
        s.reflect = True
        self.assertEqual(str(s), '(begin=0, skip=2, repeats=1, reflect=True)')
