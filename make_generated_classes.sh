#!/bin/bash

pushd src
/development/make_pyx/make_pyx.py tdsp/color/fade.h tdsp/color/combiner.h tdsp/color/stripe.h tdsp/color/render3.h
popd
