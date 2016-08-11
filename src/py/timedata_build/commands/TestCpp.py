from . Command import *
from .. import execute

class TestCpp(Command):
    description = 'Build and run C++ tests.  Might not work on windows.'

    def run(self):
        print(execute.run('make'))
        print(execute.run('./build/tests'))
