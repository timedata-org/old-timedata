import re
from . Command import *
from .. config import CONFIG, FLAGS
from .. import read_classes, write_class, make_structs, files


class Generate(Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def _structs(self, template_directory):
        prefix = CONFIG.code_generation['struct_prefix']
        structs = CONFIG.code_generation['struct_files']
        return make_structs.make_structs(prefix, structs, template_directory)

    def _classes(self, template_directory):
        for c in read_classes.read_classes(FLAGS.models):
            yield write_class.write_class(
                template_directory=template_directory, **c)

    def run(self):
        tmpl = CONFIG.code_generation['template_directory']
        filenames = self._structs(tmpl) + list(self._classes(tmpl))

        data = ''.join('include "%s"\n' % f for f in sorted(filenames))
        outfile = CONFIG.code_generation['output_file']
        files.write_if_different(outfile, data)
