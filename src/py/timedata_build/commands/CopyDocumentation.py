import os
from distutils.dir_util import copy_tree
from . Command import *


class CopyDocumentation(Command):
    description = 'Copy documentation to github.io repository'

    def run(self):
        f = lambda s: os.path.abspath(CONFIG.directories[s])
        copy_tree(f('sphinx'), f('documentation'))
