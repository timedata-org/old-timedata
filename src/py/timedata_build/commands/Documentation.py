import os
from . Command import *
from .. import files


class Documentation(Command):
    description = 'Build Sphinx documentation and copy source files'

    def run(self):
        pass
        # doc_dir = CONFIG.directories['documentation']
        # genfile_dir = CONFIG.directories['genfiles']
        # cpp_dir = os.path.join(doc_dir, 'cpp')
        # pyx_dir = os.path.join(doc_dir, 'pyx')
        # files.make_directories(cpp_dir, pyx_dir)
        # files.copy_tree(os.path.join(genfile_dir, 'pyx'
