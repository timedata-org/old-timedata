import os
from .. import files
from . Command import *


class CopyDocumentation(Command):
    description = 'Copy documentation to github.io repository'

    def run(self):
        files.copy_tree(DIRS.documentation, DIRS.documentation_repo)
