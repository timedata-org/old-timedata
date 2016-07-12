RUN="python3 setup.py clean generate --tiny build_ext develop benchmark"

$RUN

$RUN --compileropt=
$RUN --compileropt= --buildtype=o3
$RUN --compileropt= --buildtype=debug

$RUN --compileropt=-ffast-math
$RUN --compileropt=-flto
$RUN --compileropt=-fno-math-errno
$RUN --compileropt=-fomit-frame-pointer
$RUN --compileropt=-fprofile-generate
$RUN --compileropt=-ftree-vectorize
$RUN --compileropt=-funroll-loops
