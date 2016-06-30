import unittest

from timedata import compile_timestamp, NewColors, NewColors256, NewColor, NewColor256

class TestGeneral(unittest.TestCase):
    def test_timestamp(self):
        self.assertEqual(len(compile_timestamp()), 26)
        self.assertEqual(compile_timestamp()[:3], '201')

class TestNewColors(unittest.TestCase):
    def test_all(self):
        self.assertEqual(NewColors.red, NewColor('red'))
        self.assertEqual(NewColors256.cyan, NewColor256('cyan'))
