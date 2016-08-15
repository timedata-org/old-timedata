from . Benchmark import Benchmark
from . BuildExt import BuildExt
from . Clean import Clean
from . CopyDocumentation import CopyDocumentation
from . Documentation import Documentation
from . Generate import Generate
from . TestCpp import TestCpp

COMMANDS = dict(
    benchmark=Benchmark,
    build_ext=BuildExt,
    clean=Clean,
    copy_documentation=CopyDocumentation,
    documentation=Documentation,
    generate=Generate,
    test_cpp=TestCpp,
    )
