cdef extern from "<timedata/base/timestamp.h>" namespace "timedata":
    string compileTimestamp()
    string gitTags()

def compile_timestamp():
    """Return a string with the compilation time of this module in UTC."""
    return compileTimestamp().decode('ascii')

def git_tags():
    return gitTags().decode('ascii')

def timestamp():
    return 'timedata compiled on %s with tags %s' % (
        compile_timestamp(), git_tags())
