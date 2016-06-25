Test code for timedata
=============

This directory contains only Python scripts to test the _timedata_ Python extension.

The great majority of the source is C++ and Cython code contained in the
top-level `src/timedata` directory.

The build process will also move a `timedata.so` file into this directory so
you can directly `import timedata` from here.
