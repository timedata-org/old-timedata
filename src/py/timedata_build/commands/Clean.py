import os, pathlib, shutil
from . Command import *

class Clean(Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        dirs = CONFIG.code_generation['clean_directories']
        for d in dirs:
            print('Deleting ./{}/'.format(d))
            shutil.rmtree(os.path.abspath(d), ignore_errors=True)

        for f in CONFIG.code_generation['clean_files']:
            try:
                os.remove(f)
            except:
                pass
        for s in list(pathlib.Path('src').glob('**/*.html')):
            os.remove(str(s))
