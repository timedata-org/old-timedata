#!/bin/bash

pushd src
/development/make_pyx/make_pyx.py \
    tdsp/signal/fade.h \
    tdsp/signal/combiner.h \
    tdsp/signal/render3.h\
    tdsp/signal/stripe.h\

popd
