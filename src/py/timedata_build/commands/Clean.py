import os, pathlib, shutil
from . Command import *


class Clean(Command):
    description = 'Complete clean command'

    NAME = 'files'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        for filename in CONFIG.clean[self.NAME]:
            for path in pathlib.Path('.').glob(filename):
                f = str(path)
                print('Deleting ./{}/'.format(f))
                try:
                    shutil.rmtree(os.path.abspath(f))
                except:
                    try:
                        os.remove(f)
                    except:
                        pass
