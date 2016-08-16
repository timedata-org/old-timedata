import os, shutil, time
from . Command import *
from .. import files


class Documentation(Command):
    description = 'Build Sphinx documentation and copy source files'

    def run(self):
        pyx_dir = files.clean_dir(DIRS.documentation, 'src', 'pyx')
        files.copy_tree(DIRS.genfiles, pyx_dir)

        cpp_dir = files.clean_dir(DIRS.documentation, 'src', 'cpp')
        shutil.copy(os.path.abspath('timedata.cpp'),
                    os.path.join(cpp_dir, 'timedata.cpp'))
