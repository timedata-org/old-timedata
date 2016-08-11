import configparser, re

class Context(object):
    def __init__(self, **kwds):
        for (k, v) in kwds.items():
            setattr(self, k, v)


def config(filename='setup.cfg', prefix='timedata_'):
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

CONFIG = config()
