import os, sys

from . import util


def extract_env(**flags):
    get = lambda k, v: os.environ.get('TIMEDATA_' + k.upper(), v)
    return util.Context(**{k: get(k, v) for k, v in flags.items()})


def insert_dependencies(args, **dependencies):
    result = []
    def add_all(*args):
        for arg in args:
            deps = dependencies.get(arg, [])
            if isinstance(deps, (list, tuple)):
                add_all(*deps)
            else:
                add_all(deps)
            (arg in result) or result.append(arg)

    add_all(*args)
    return result
