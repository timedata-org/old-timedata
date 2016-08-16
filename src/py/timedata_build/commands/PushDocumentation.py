from .. import execute
from . Command import *

class PushDocumentation(Command):
    description = 'Push documentation to github.io'

    def run(self):
        # TODO: dodgy, should probably delete.
        execute.git_push(DIRS.documentation_repo, TIME)
