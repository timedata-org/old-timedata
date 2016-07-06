cdef extern from "<timedata/color/names_table_inl.h>" namespace "timedata":
    vector[string]& colorNames()

def _colors_by_name(color_class):
    cdef vector[string] cnames = colorNames()
    class Object(object):
        pass

    names, result = [], Object()
    for i in cnames:
        name = i.decode('ascii')
        names.append(name)
        setattr(result, name.replace(' ', '_'), color_class(name))
    return tuple(sorted(names)), result
