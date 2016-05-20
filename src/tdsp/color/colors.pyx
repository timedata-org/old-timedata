class Colors(object):
    """Colors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class Colors256(object):
    """Colors256 is a convenience class whose static members are named
       colors, like Colors256.red, or Colors256.deep_sky_blue."""
    pass


def _load_colors():
    for name in Color.names():
        setattr(Colors, name.replace(' ', '_'), Color(name))

    for name in Color256.names():
        setattr(Colors256, name.replace(' ', '_'), Color256(name))

    for i in range(1, 100):
        for gray in 'gray', 'grey':
            name = '%s %d' % (gray, i)
            attr = '%s_%d' % (gray, i)
            for cs, c in (Colors, Color), (Colors256, Color256):
                setattr(cs, attr, c(name))
