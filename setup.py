#!/usr/bin/env python3

import sys, unittest
from setuptools.command.build_ext import build_ext
import setuptools.extension
import Cython.Compiler.Options


sys.path.append('src/py')
from timedata_build import arguments, commands, context

CONFIG = context.CONFIG

arguments.check_python(CONFIG.flags['minimum_python_version'])

"""Each of these "flags" corresponds to an environment variable looking like
   TIMEDATA_$NAME, where $NAME is the uppercase version of flag.

   For example, to run generate with the "tiny" flag, enter:

       TIMEDATA_TINY=true ./setup.py generate
"""
sys.argv = arguments.insert_dependencies(sys.argv, **CONFIG.dependencies)

# See: http://goo.gl/1kNY1n
Cython.Compiler.Options.annotate = CONFIG.flags['annotate'].lower() == 'true'


# http://stackoverflow.com/a/37033551/43839
def test_suite():
    return unittest.TestLoader().discover('src/py', pattern='*_test.py')


print('Building targets', *sys.argv[1:])
setuptools.setup(cmdclass=commands.COMMANDS, **CONFIG.setuptools)
