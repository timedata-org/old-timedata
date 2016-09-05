import re
from . Command import *
from timedata_build import generate
from timedata_build.config import CONFIG, FLAGS


class Generate(Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def run(self):
        print('Generate ' + ('tiny' if FLAGS.tiny else ''))

        models = FLAGS.models and re.split('[\W,]', FLAGS.models)
        generate.generate(
            models=models,
            outfile=CONFIG.code_generation['output_file'],
            structs=CONFIG.code_generation['struct_files'],
            template_directory=CONFIG.code_generation['template_directory'],
            tiny=FLAGS.tiny,
            )
