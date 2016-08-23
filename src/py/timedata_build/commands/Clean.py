import os, pathlib, shutil
from . Command import *

CLEAN_FILES = 'timedata.html', 'timedata.so'

class Clean(Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        print('Deleting ./{}/'.format(DIRS.build))
        shutil.rmtree(DIRS.build, ignore_errors=True)

        for f in CLEAN_FILES:
            try:
                os.remove(f)
            except:
                pass
        for s in list(pathlib.Path('src').glob('**/*.html')):
            os.remove(str(s))
