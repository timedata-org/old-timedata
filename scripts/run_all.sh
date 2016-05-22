source /development/env/cython/bin/activate && \
    rm -Rf build *.so && \
    python setup.py clean && \
    python setup.py build_ext && \
    make && \
    build/tests && \
    ./run_python_tests.sh
