import os, shutil
from . Command import *


class Clean(Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        print('Deleting ./{}/'.format(DIRS.build))
        shutil.rmtree(DIRS.build, ignore_errors=True)
