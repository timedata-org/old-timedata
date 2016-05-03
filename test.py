from tdsp.tdsp import Color

"""Code to test the tdsp binary module."""

print(Color())
print(Color(1, 1, 1))
for i in range(1000):
    Color(0.5, 0.5, 0.5)
    Color(0.25, 0.25, 0.25)
print(Color.make('red'))
