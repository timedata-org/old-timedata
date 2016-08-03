cdef extern from "<timedata/base/timestamp.h>" namespace "timedata":
    string compileTimestamp()
    string gitTags()
    string optimizationFlags()

def compile_timestamp():
    """Return a string with the compilation time of this module in UTC."""
    return compileTimestamp().decode('ascii')

def git_tags():
    """Return a string representing the git branch and commit ID that this
       release of timedata was compiled with."""
    return gitTags().decode('ascii')

def optimization_flags():
    """Return a string with the optimization flags passed to the compiler
       and linker.

       Useful for benchmarks so you can experiment with different
       optimization flags and automatically record the results."""
    return optimizationFlags().decode('ascii')

def print_startup_message():
    """Print a string with the startup message.

       To silence the printing of this message at startup, set the
       environment variable TIMEDATA_SILENT_STARTUP."""
    import os
    if not os.environ.get('TIMEDATA_SILENT_STARTUP'):
        print('timedata: compiled', compile_timestamp(), '; tags', git_tags())
