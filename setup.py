#!/usr/bin/env python3

"""This is the main builder and installer for the timedata DSP Python
extension.
"""

import configparser, datetime, errno, glob, os, platform
import re, shutil, sys, subprocess, unittest

from distutils.dir_util import copy_tree
from setuptools.command.build_ext import build_ext
import setuptools.extension
import Cython.Compiler.Options

sys.path.append('src/py')
from timedata_build import arguments, commands, context, execute, generate, template

CONFIG = context.CONFIG

"""Each of these "flags" corresponds to an environment variable looking like
   TIMEDATA_$NAME, where $NAME is the uppercase version of flag.

   For example, to run generate with the "tiny" flag, enter:

       TIMEDATA_TINY=true ./setup.py generate
"""
FLAGS = arguments.FLAGS
sys.argv = arguments.insert_dependencies(sys.argv, **CONFIG.dependencies)

print('Building targets', *sys.argv[1:])

LEAST_PYTHON = 3, 4
ACTUAL_PYTHON = sys.version_info[:2]

assert ACTUAL_PYTHON >= LEAST_PYTHON, (
    'Must use at least Python %d.%d but have version %d.%d' %
    (LEAST_PYTHON[0], LEAST_PYTHON[1], ACTUAL_PYTHON[0], ACTUAL_PYTHON[1]))

IS_DEBIAN = platform.linux_distribution()[0] == 'debian'
IS_WINDOWS = platform.system() == 'windows'

LIBRARIES = ['m'] if IS_DEBIAN else []
TIME = datetime.datetime.utcnow().isoformat()

# See: http://goo.gl/1kNY1n
Cython.Compiler.Options.annotate = bool(CONFIG.flags['annotate'])


def compiler_flags():
    flags = CONFIG.compiler_flags[platform.system().lower()]
    git_tags = execute.git_tags()
    return template.substitute_one(flags, git_tags=git_tags, time=TIME).split()


class Benchmark(commands.Command):
    description = 'Run benchmark'

    def run(self):
        print('Benchmark')
        from benchmark.benchmark import run_benchmarks
        name = FLAGS.name
        if not name:
            parts = [FLAGS.buildtype]
            for o in FLAGS.compileropt.split():
                parts.append(o[2:])
            name = '_'.join(parts)
        run_benchmarks(FLAGS.benchmarks.split(','), '-'.join(parts),
                       FLAGS.benchmark_size, FLAGS.benchmark_number)


class BuildExt(build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

    def finalize_options(self):
        try:
            import Cython.Build
        except:
            print('You need to install Cython for a binary build:',
                  'http://docs.cython.org/src/quickstart/install.html')
            raise
        os.makedirs('build/genfiles/timedata', exist_ok=True)
        compile_args = compiler_flags()

        opt_flags = None
        if not IS_WINDOWS:
            opt_flags = CONFIG.build_options[FLAGS.buildtype or 'o3'].split()
            if FLAGS.compileropt:
                opt_flags += FLAGS.compileropt.split()
            compile_args += opt_flags
            compile_args.append(
                '-DOPTIMIZATION_FLAGS="%s"' % ' '.join(sorted(opt_flags)))

        extension = setuptools.extension.Extension(
            name='timedata',
            sources=['timedata.pyx'],
            libraries=LIBRARIES,
            include_dirs=['src/cpp'],
            extra_compile_args=compile_args,
            extra_link_args=opt_flags,
            language='c++',
        )

        module = Cython.Build.cythonize(
            [extension],
            language='c++',
            language_level=3,

            compiler_directives=dict(
                c_string_encoding='ascii',
                # c_string_type='unicode', # Why doesn't this work?
            )
        )
        self.distribution.ext_modules = module
        super().finalize_options()


class Clean(commands.Command):
    description = 'Complete clean command'

    def initialize_options(self):
        self.cwd = None

    def finalize_options(self):
        self.cwd = os.getcwd()

    def run(self):
        d = CONFIG.directories['build']
        print('Deleting ./{}/'.format(d))
        shutil.rmtree(os.path.abspath(d), ignore_errors=True)


class CopySphinx(commands.Command):
    description = 'Push documentation to github.io'

    def run(self):
        f = lambda s: os.path.abspath(CONFIG.directories[s])
        copy_tree(f('sphinx'), f('documentation'))


class PushSphinx(commands.Command):
    description = 'Push documentation to github.io'

    def run(self):
        execute.git_push(CONFIG.directories['documentation'], TIME)


class TestCpp(commands.Command):
    description = 'Build and run C++ tests.  Might not work on windows.'

    def run(self):
        print(execute.run('make'))
        print(execute.run('./build/tests'))


class Generate(commands.Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def run(self):
        print('Generate ' + ('tiny' if FLAGS.tiny else ''))

        models = FLAGS.models and re.split('[\W,]', FLAGS.models)
        generate.generate(tiny=FLAGS.tiny, models=models)


COMMANDS = {
    'benchmark': Benchmark,
    'build_ext': BuildExt,
    'clean': Clean,
    'copy_sphinx': CopySphinx,
    'generate': Generate,
    'push_sphinx': PushSphinx,
    'test_cpp': TestCpp,
    }


# http://stackoverflow.com/a/37033551/43839
def test_suite():
    return unittest.TestLoader().discover('src/py', pattern='*_test.py')


setuptools.setup(cmdclass=COMMANDS, **CONFIG.setuptools)
