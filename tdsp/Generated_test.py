import unittest

from tdsp import Stripe

class TestGenerated(unittest.TestCase):
    def test_trivial(self):
        s = Stripe()
        self.assertEqual(str(s), '(begin=0, skip=1, repeats=1, reflect=False)')
        self.assertEqual(
            repr(s), 'tdsp.Stripe(begin=0, skip=1, repeats=1, reflect=False)')
