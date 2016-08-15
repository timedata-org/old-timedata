import re
from . Command import *
from timedata_build import generate


class Generate(Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def run(self):
        print('Generate ' + ('tiny' if FLAGS.tiny else ''))

        models = FLAGS.models and re.split('[\W,]', FLAGS.models)
        generate.generate(tiny=FLAGS.tiny, models=models)
