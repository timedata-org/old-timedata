import os
from distutils.dir_util import copy_tree
from . Command import *


class CopySphinx(Command):
    description = 'Push documentation to github.io'

    def run(self):
        f = lambda s: os.path.abspath(CONFIG.directories[s])
        copy_tree(f('sphinx'), f('documentation'))
