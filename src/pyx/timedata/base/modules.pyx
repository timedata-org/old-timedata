def _make_module():
    def make(package, name, **kwds):
        import types
        m = types.ModuleType(name)
        package = package + '.' + name
        m.__package__ = package
        for k, v in kwds.items():
            if isinstance(v, dict):
                v = make(package, k, **v)
            setattr(m, k, v)
        return m

    normal = dict(
        Color=Color,
        ColorList=ColorList)

    return make(
        'timedata', 'color',
        rgb=dict(
            normal=normal,
            c255=dict(
                Color=Color255,
                ColorList=ColorList255),
            c256=dict(
                Color=Color256,
                ColorList=ColorList256),
            **normal),
        **normal)
