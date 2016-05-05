from tdsp.tdsp import Color, ColorList

"""Code to test the tdsp binary module."""

white = Color(1, 1, 1)
print(white[:])
print(white[0:2])
print(white[::-1])

print(Color())
print(Color(1, 1, 1))
for i in range(1000):
    Color(0.5, 0.5, 0.5)
    Color(0.25, 0.25, 0.25)
print(Color.make('red'))
print(Color(0.5, -0.5, -0.5))
print(ColorList())
print(ColorList([[1, 1, 1]]))
print(ColorList(('red', 'green')))
