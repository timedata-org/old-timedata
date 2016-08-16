import os, shutil, time
from . Command import *
from .. import files


class Documentation(Command):
    description = 'Build Sphinx documentation and copy source files'

    def run(self):
        cpp_dir = os.path.join(DIRS.documentation, 'src', 'cpp')
        pyx_dir = os.path.join(DIRS.documentation, 'src', 'pyx')
        shutil.rmtree(cpp_dir, ignore_errors=True)
        shutil.rmtree(pyx_dir, ignore_errors=True)
        os.makedirs(cpp_dir)
        os.makedirs(pyx_dir)
        files.copy_tree(DIRS.genfiles, pyx_dir)
        shutil.copy(os.path.abspath('timedata.cpp'),
                    os.path.join(cpp_dir, 'timedata.cpp'))
