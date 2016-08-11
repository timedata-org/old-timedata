from .. import execute
from . Command import *

class PushSphinx(Command):
    description = 'Push documentation to github.io'

    def run(self):
        execute.git_push(CONFIG.directories['documentation'], TIME)
