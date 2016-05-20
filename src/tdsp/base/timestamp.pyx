cdef extern from "<tdsp/base/timestamp.h>" namespace "tdsp":
    string getCompileTimestamp()

def compile_timestamp():
    """Return a string with the compilation time of this module in UTC."""
    return getCompileTimestamp().decode('ascii')
