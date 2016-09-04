import configparser, os, re

from . import git


class Context(object):
    def __init__(self, *items, **kwds):
        def run(x):
            for k, v in x.items():
                setattr(self, k, v)
        for i in items:
            run(i.__dict__)
        run(kwds)


def public_dir(x):
    return {k: v for (k, v) in x.__dict__.items() if not k.startswith('_')}


def config(filename='setup.cfg', prefix=None):
    prefix = prefix or (git.project() + '_')
    parser = configparser.ConfigParser()
    parser.read_file(open(filename))

    result = {}
    for section_name, section in parser.items():
        if section_name.startswith(prefix):
            def fix(x):
                x = x.replace('\n', ' ').strip()
                if x and x.startswith('[') and x.endswith(']'):
                    return x[1:-1].split()
                return x

            section_dict = {k: fix(v) for k, v in section.items()}
            section_name = section_name[len(prefix):]
            result[section_name] = section_dict

    return Context(**result)


def read_flags_from_environ(*, prefix=None, **flags):
    prefix = prefix or (git.project().upper() + '_')
    result = {}
    for key, v in flags.items():
        value = os.environ.get(prefix + key.upper(), v)
        if value.lower() == 'true':
            value = True
        elif value.lower() == 'false':
            value = False
        result[key] = value
    return Context(**result)


CONFIG = config()
DIRS = Context(**{k: os.path.abspath(v) for k, v in CONFIG.directories.items()})
FLAGS = read_flags_from_environ(**CONFIG.flags)

"""
TODO: this comment need to be extracted into an external doc.
Each of these "flags" corresponds to an environment variable looking like
   TIMEDATA_$NAME, where $NAME is the uppercase version of flag.

   For example, to run generate with the "tiny" flag, enter:

       TIMEDATA_TINY=true ./setup.py generate
"""
