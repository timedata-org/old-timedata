cdef extern from "<tdsp/base/timestamp.h>" namespace "tdsp":
    string getCompileTimestamp()

def compile_timestamp():
    return getCompileTimestamp().decode('ascii')
