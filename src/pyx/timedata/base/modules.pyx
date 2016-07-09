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

            hsl=dict(
                normal=dict(Color=ColorHSL, ColorList=ColorListHSL),
                c255=dict(Color=ColorHSL255, ColorList=ColorListHSL255),
                c256=dict(Color=ColorHSL256, ColorList=ColorListHSL256),
                Color=ColorHSL, ColorList=ColorListHSL),

            hsv=dict(
                normal=dict(Color=ColorHSV, ColorList=ColorListHSV),
                c255=dict(Color=ColorHSV255, ColorList=ColorListHSV255),
                c256=dict(Color=ColorHSV256, ColorList=ColorListHSV256),
                Color=ColorHSV, ColorList=ColorListHSV),

            yiq=dict(
                normal=dict(Color=ColorYIQ, ColorList=ColorListYIQ),
                c255=dict(Color=ColorYIQ255, ColorList=ColorListYIQ255),
                c256=dict(Color=ColorYIQ256, ColorList=ColorListYIQ256),
                Color=ColorYIQ, ColorList=ColorListYIQ),

            Color=ColorRGB, ColorList=ColorListRGB),

        Color=ColorRGB, ColorList=ColorListRGB).__dict__

    return {k: v for (k, v) in d.items() if not k.startswith('_')}
