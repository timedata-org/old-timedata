import os, shutil
from . Command import *


class Clean(Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        d = CONFIG.directories['build']
        print('Deleting ./{}/'.format(d))
        shutil.rmtree(os.path.abspath(d), ignore_errors=True)
