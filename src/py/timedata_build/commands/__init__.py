from . Benchmark import Benchmark
from . BuildExt import BuildExt
from . Clean import Clean
from . CopySphinx import CopySphinx
from . Generate import Generate
from . PushSphinx import PushSphinx
from . TestCpp import TestCpp


COMMANDS = dict(
    benchmark=Benchmark,
    build_ext=BuildExt,
    clean=Clean,
    copy_sphinx=CopySphinx,
    generate=Generate,
    push_sphinx=PushSphinx,
    test_cpp=TestCpp,
    )
