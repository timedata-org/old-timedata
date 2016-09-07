import os, pathlib, platform, shutil
import setuptools.extension
import Cython.Build

from setuptools.command.build_ext import build_ext
from . Command import CONFIG, DIRS, FLAGS, TIME
from .. import execute, files, template


class BuildExt(build_ext):
    # See https://groups.google.com/forum/#!topic/cython-users/IZMENRz6__s

    def _extension_dict(self):
        flags = CONFIG.compiler_flags[platform.system().lower()]
        git_tags = execute.git_tags()
        compile_args = template.substitute_one(
            flags, git_tags=git_tags, time=TIME).split()

        opt_flags = None
        if not platform.system() == 'Windows':
            opt_flags = CONFIG.build_options[FLAGS.buildtype or 'o3'].split()
            if FLAGS.compileropt:
                opt_flags += FLAGS.compileropt.split()
            compile_args += opt_flags
            compile_args.append(
                '-DOPTIMIZATION_FLAGS="%s"' % ' '.join(sorted(opt_flags)))
        is_debian = platform.linux_distribution()[0] == 'debian'
        libraries = ['m'] if is_debian else []
        libraries += CONFIG.linker['libraries']

        return dict(
            libraries=libraries,
            extra_compile_args=compile_args,
            extra_link_args=opt_flags,
            language='c++',
            **CONFIG.extension_arguments)

    def finalize_options(self):
        os.makedirs(DIRS.genfiles_project, exist_ok=True)
        extension = setuptools.extension.Extension(**self._extension_dict())
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

    def run(self):
        super().run()
        afile = files.clean_dir(DIRS.documentation, 'annotation')
        for f in CONFIG.code_generation['discarded_html']:
            try:
                os.remove(f)
            except:
                pass

        html_path = CONFIG.code_generation['html_path']
        source_pyx = pathlib.Path(html_path).glob('**/*.html')
        genfiles_pyx = pathlib.Path(DIRS.genfiles).glob('**/*.html')
        for s in list(source_pyx) + list(genfiles_pyx):
            src = str(s)
            parts = files.splitall(src)
            while parts[0] != CONFIG.setuptools['name']:
                parts.pop(0)
            target = os.path.join(afile, *parts)
            os.makedirs(os.path.dirname(target), exist_ok=True)
            try:
                shutil.move(src, target)
            except:
                pass
