cdef extern from "fcolor2/Rows.h" namespace "fcolor":
    int computeRows(int size, int columns)

def compute_rows(int size, int columns):
    return computeRows(size, columns)
