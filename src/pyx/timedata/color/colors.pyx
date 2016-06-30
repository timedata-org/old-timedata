class Colors(object):
    """Colors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class Colors255(object):
    """Colors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class Colors256(object):
    """Colors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


def _load_colors():
    for cs, c in (
            (Colors, Color),
            (Colors255, Color255),
            (Colors256, Color256),
            ):
        for name in c.names():
            setattr(cs, name.replace(' ', '_'), c(name))

        for i in range(1, 100):
            for gray in 'gray', 'grey':
                name = '%s %d' % (gray, i)
                attr = '%s_%d' % (gray, i)
                setattr(cs, attr, c(name))
