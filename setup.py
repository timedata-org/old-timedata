#!/usr/bin/env python3

import setuptools, sys, unittest
import Cython.Compiler.Options

SOURCE_PATH = 'src/py'

sys.path.append(SOURCE_PATH)
from timedata_build import COMMANDS, CONFIG, FLAGS
from timedata_build import check_python, insert_dependencies

# http://stackoverflow.com/a/37033551/43839
def test_suite():
    return unittest.TestLoader().discover(
        SOURCE_PATH, pattern=FLAGS.test_pattern)


check_python(FLAGS.minimum_python_version)
sys.argv = insert_dependencies(sys.argv, **CONFIG.dependencies)

# See: http://goo.gl/1kNY1n
Cython.Compiler.Options.annotate = FLAGS.annotate.lower() == 'true'

print('About to build targets', *sys.argv[1:])
setuptools.setup(cmdclass=COMMANDS, **CONFIG.setuptools)

"""
TODO: this comment need to be extracted into an external doc.
Each of these "flags" corresponds to an environment variable looking like
   TIMEDATA_$NAME, where $NAME is the uppercase version of flag.

   For example, to run generate with the "tiny" flag, enter:

       TIMEDATA_TINY=true ./setup.py generate
"""
