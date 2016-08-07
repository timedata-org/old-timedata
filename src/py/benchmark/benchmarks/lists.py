from timedata import Color, ColorList

BLACK = Color.by_name.black


def make_data(size):
    return ColorList().resize(size), ColorList().resize(size)


def benchmarks():
    def replace_all(x, y):
        x[:] = y

    def compare(x, y):
        x < y

    def rotate(x, y):
        x.rotate(len(x) / 8)

    def rotate_to(x, y):
        x.rotate_to(len(x) / 8, y)

    def invert(x, y):
        x.invert()

    def add_list(x, y):
        x.add(y)

    def add_to_list(x, y):
        x.add_to(y, y)

    def add_color(x, y):
        x.add(BLACK)

    def add_to_color(x, y):
        x.add_to(BLACK, y)

    def add_number(x, y):
        x.add(0)

    def add_to_number(x, y):
        x.add_to(0, y)

    return sorted(locals().items())
