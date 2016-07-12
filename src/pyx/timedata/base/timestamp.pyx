cdef extern from "<timedata/base/timestamp.h>" namespace "timedata":
    string compileTimestamp()
    string gitTags()
    string optimizationFlags()

def compile_timestamp():
    """Return a string with the compilation time of this module in UTC."""
    return compileTimestamp().decode('ascii')

def git_tags():
    return gitTags().decode('ascii')

def optimization_flags():
    return optimizationFlags().decode('ascii')

def startup_message():
    return 'timedata: compiled %s; tags %s' % (compile_timestamp(), git_tags())
