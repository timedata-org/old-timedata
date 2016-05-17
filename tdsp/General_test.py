import unittest

from tdsp import compile_timestamp, Colors, Colors256, Color, Color256

class TestGeneral(unittest.TestCase):
    def test_timestamp(self):
        self.assertEqual(len(compile_timestamp()), 26)
        self.assertEqual(compile_timestamp()[:3], '201')

class TestColors(unittest.TestCase):
    def test_all(self):
        self.assertEqual(Colors.red, Color('red'))
        self.assertEqual(Colors256.cyan, Color256('cyan'))
