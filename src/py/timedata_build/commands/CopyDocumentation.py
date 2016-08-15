import os
from .. import files
from . Command import *


class CopyDocumentation(Command):
    description = 'Copy documentation to github.io repository'

    def run(self):
        get = CONFIG.directories
        files.copy_tree(
            CONFIG.directories['documentation'],
            CONFIG.directories['documentation_repo'])
