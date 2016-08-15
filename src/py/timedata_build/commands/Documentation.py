import os
from distutils.dir_util import copy_tree
from . Command import *


class Documentation(Command):
    description = 'Build Sphinx documentation and copy source files'

    def run(self):
        pass
