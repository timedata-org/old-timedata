import unittest

from tdsp import Color

class TestColor(unittest.TestCase):
    def test_white(self):
        white = Color(1, 1, 1)
        self.assertEqual(str(white), 'white')
        self.assertEqual(white[:], white)
        self.assertEqual(white[::-1], white)
        self.assertEqual(white[0:2], (1.0, 1.0))

    def test_red(self):
        red = Color(1, 0, 0)
        blue = Color('blue')

        self.assertEqual(str(red), 'red')
        self.assertEqual(red[:], red)
        self.assertEqual(red[::-1], blue)
        self.assertEqual(red[0:2], (1.0, 0.0))

    def test_add(self):
        red = Color('red')
        self.assertEqual(Color('red') + Color('green'), Color('yellow'))

# print(Color())
# print(Color(1, 1, 1))
# for i in range(1000):
#     Color(0.5, 0.5, 0.5)
#     Color(0.25, 0.25, 0.25)
# print(Color.make('red'))
# print(Color(0.5, -0.5, -0.5))
# print(ColorList())
# print(ColorList([[1, 1, 1]]))
# print(ColorList(('red', 'green')))
