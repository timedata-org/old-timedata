def _make_module():
    def make(package, name, **kwds):
        import types
        m = types.ModuleType(name)
        package = package + ('.' if package else '') + name
        m.__package__ = package
        for k, v in kwds.items():
            if isinstance(v, dict):
                v = make(package, k, **v)
            setattr(m, k, v)
        return m

    def add(d, key, name):
        c = globals().get('Color' + name)
        cl = globals().get('ColorList' + name)
        cnst = globals().get('ColorConst' + name)
        if c and cl and cnst:
            d[key] = dict(Color=c, ColorList=cl, ColorConst=cnst)

    normal = dict(
        Color=ColorRGB,
        ColorConst=ColorConstRGB,
        ColorList=ColorListRGB,
        )

    rgb = dict(normal=normal, **normal)
    add(rgb, 'c255', 'RGB255')
    add(rgb, 'c256', 'RGB256')

    color = dict(rgb=rgb, **normal)
    add(color, 'hsl', 'HSL')
    add(color, 'hsv', 'HSV')
    add(color, 'xyz', 'XYZ')
    add(color, 'yiq', 'YIQ')
    add(color, 'yuv', 'YUV')

    d = make('', 'timedata', color=color, **normal).__dict__

    return {k: v for (k, v) in d.items() if not k.startswith('_')}
