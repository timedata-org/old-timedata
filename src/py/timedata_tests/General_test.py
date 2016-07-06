import unittest

from timedata import compile_timestamp

class TestGeneral(unittest.TestCase):
    def test_timestamp(self):
        self.assertEqual(len(compile_timestamp()), 26)
        self.assertEqual(compile_timestamp()[:3], '201')
