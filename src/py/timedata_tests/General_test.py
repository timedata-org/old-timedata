import unittest

from timedata import *

class TestGeneral(unittest.TestCase):
    def test_timestamp(self):
        self.assertEqual(len(compile_timestamp()), 26)
        self.assertEqual(compile_timestamp()[:3], '201')
        self.assertIsInstance(git_tags(), str)
        self.assertIsInstance(optimization_flags(), str)
