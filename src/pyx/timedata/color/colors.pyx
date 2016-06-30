class OldColors(object):
    """Colors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class OldColors256(object):
    """Colors256 is a convenience class whose static members are named
       colors, like Colors256.red, or Colors256.deep_sky_blue."""
    pass

class NewColors(object):
    """NewColors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class NewColors255(object):
    """NewColors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


class NewColors256(object):
    """NewColors is a convenience class whose static members are named Colors, like
       Colors.red, or Colors.deep_sky_blue."""
    pass


def _load_colors():
    for cs, c in (
            (OldColors, OldColor),
            (OldColors256, OldColor256),
            (NewColors, NewColor),
            (NewColors255, NewColor255),
            (NewColors256, NewColor256),
            ):
        for name in c.names():
            setattr(cs, name.replace(' ', '_'), c(name))

        for i in range(1, 100):
            for gray in 'gray', 'grey':
                name = '%s %d' % (gray, i)
                attr = '%s_%d' % (gray, i)
                setattr(cs, attr, c(name))
