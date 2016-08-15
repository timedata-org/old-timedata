from . Benchmark import Benchmark
from . BuildExt import BuildExt
from . Clean import Clean
from . CopyDocumentation import CopyDocumentation
from . Generate import Generate
from . PushDocumentation import PushDocumentation
from . TestCpp import TestCpp


COMMANDS = dict(
    benchmark=Benchmark,
    build_ext=BuildExt,
    clean=Clean,
    copy_documentation=CopyDocumentation,
    generate=Generate,
    push_documentation=PushDocumentation,
    test_cpp=TestCpp,
    )
