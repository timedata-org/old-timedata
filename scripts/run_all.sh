# Cleans everything and reruns all the build and the tests.

source /development/env/cython/bin/activate && \
  scripts/make_generated_classes.py && \
  rm -Rf build *.so && \
  python setup.py clean && \
  python setup.py build_ext && \
  python setup.py local && \
  make && build/tests && \
  python -m unittest discover -p \*_test.py
