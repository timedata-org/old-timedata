import re
from . Command import *
from timedata_build import generate


class Generate(Command):
    description = 'Make generated classes'
    split_flag = re.compile('[\W,]').split

    def run(self):
        tiny = FLAGS.tiny.lower() == 'true'
        print('Generate ' + ('tiny' if tiny else ''))

        models = FLAGS.models and re.split('[\W,]', FLAGS.models)
        generate.generate(tiny=tiny, models=models)
