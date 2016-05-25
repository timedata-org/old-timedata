cdef extern from "<tada/base/timestamp.h>" namespace "tada":
    string getCompileTimestamp()

def compile_timestamp():
    """Return a string with the compilation time of this module in UTC."""
    return getCompileTimestamp().decode('ascii')
