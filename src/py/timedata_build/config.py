import configparser, os, re

from . import git
from . context import Context


def clean_entry(s):
    s = s.replace('\n', ' ').strip()
    if not s.startswith('['):
        return s

    result, remains = [], s
    while remains.startswith('['):
        try:
            index = remains.index(']')
        except ValueError:
            raise ValueError('Missing ] in "%s"' % s)
        result.extend(remains[1:index].split())
        remains = remains[index + 1:].strip()
    if remains:
        raise ValueError('Extra characters "%s" at end of string "%s"' %
                         (remains, s))
    return result


def config(filename='setup.cfg', prefix=None):
    prefix = prefix or (git.project() + '_')
    parser = configparser.ConfigParser(
        interpolation=configparser.ExtendedInterpolation()
        )
    parser.read_file(open(filename))

    result = {}
    for section_name, section in parser.items():
        if section_name.startswith(prefix):
            section_dict = {k: clean_entry(v) for k, v in section.items()}
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
