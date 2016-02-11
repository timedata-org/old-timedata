cdef extern from "fcolor/Recolumn.h" namespace "fcolor":
    void recolumn(FColorList*, int oldColumns, int newColumns)
    bool mustRecolumn(int oldColumns, int newColumns)
