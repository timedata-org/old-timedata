from timedata import Color, ColorList

BLACK = (0, 0, 0)
DEBUG = False

def make_data(size):
    return [(0, 0, 0) for i in range(size)], [(0, 0, 0) for i in range(size)]


def _add_colors(c, d):
    return c[0] + d[0], c[1] + d[1], c[2] + d[2]

def _add_number(c, n):
    return c[0] + n, c[1] + n, c[2] + n


def benchmarks():
    def replace_all(x, y):
        x[:] = y

    def compare(x, y):
        return sum(i < j for i, j in zip(x, y))

    def rotate(x, y):
        n = int(len(x) / 8)
        return x[-n:] + x[:n]

    def rotate_to(x, y):
        n = int(len(x) / 8)
        y[:] = x[-n:] + x[:n]

    def invert(x, y):
        return [(1 - i, 1 - j, 1 - k) for i, j, k in x]

    def add_list(x, y):
        return [_add_colors(i, j) for i, j in zip(x, y)]

    def add_to_list(x, y):
        y[:] = [_add_colors(i, j) for i, j in zip(x, y)]

    def add_color(x, y):
        return [_add_colors(i, BLACK) for i in x]

    def add_to_color(x, y):
        y[:] = [_add_colors(i, BLACK) for i in x]

    def add_number(x, y):
        return [_add_number(i, 0) for i in x]

    def add_to_number(x, y):
        y[:] = [_add_number(i, 0) for i in x]

    items = sorted(locals().items())
    if not DEBUG:
        return items

    def annotate(name, function):
        first_time = [True]
        def f(x, y):
            if first_time:
                print(name)
                first_time[:] = []
            function(x, y)
        return f

    return [(k, annotate(k, v)) for k, v in items]
