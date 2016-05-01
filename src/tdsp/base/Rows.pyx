cdef extern from "tdsp2/Rows.h" namespace "tdsp":
    int computeRows(int size, int columns)

def compute_rows(int size, int columns):
    return computeRows(size, columns)
