import sys

from . import util


def extract_flags(args, **flags):
    result = []
    for arg in args:
        for flag in flags:
            if arg.startswith('--' + flag):
                value = arg[len(flag) + 2:]
                if not value:
                    flags[flag] = True
                elif value.startswith('='):
                    flags[flag] = value[1:]
                else:
                    raise ValueError('Can\'t understand flag ' + arg)
                break
        else:
            result.append(arg)
    args[:] = result
    return util.Context(**flags)


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
