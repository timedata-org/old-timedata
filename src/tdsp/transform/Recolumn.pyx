cdef extern from "tdsp/Recolumn.h" namespace "tdsp":
    void recolumn(FColorList*, int oldColumns, int newColumns)
    bool mustRecolumn(int oldColumns, int newColumns)
