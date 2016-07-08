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

    d = make(
        '', 'timedata',
        color=dict(
            rgb=dict(
                normal=dict(Color=ColorRGB, ColorList=ColorListRGB),
                c255=dict(Color=ColorRGB255, ColorList=ColorListRGB255),
                c256=dict(Color=ColorRGB256, ColorList=ColorListRGB256),
                Color=ColorRGB, ColorList=ColorListRGB),
            hsv=dict(
                normal=dict(Color=ColorHSV, ColorList=ColorListHSV),
                c255=dict(Color=ColorHSV255, ColorList=ColorListHSV255),
                c256=dict(Color=ColorHSV256, ColorList=ColorListHSV256),
                Color=ColorHSV, ColorList=ColorListHSV),
            Color=ColorRGB, ColorList=ColorListRGB),
        Color=ColorRGB, ColorList=ColorListRGB).__dict__

    return {k: v for (k, v) in d.items() if not k.startswith('_')}
