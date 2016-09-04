import os
from . import files


def root(path=None):
    """Returns the git root recursively containing this directory, if any."""
    path = path or os.getcwd()
    original_path = None
    last_path = None
    while path != last_path:
        if os.path.isdir(os.path.join(path, '.git')):
            return path
        last_path = path
        path = os.path.dirname(path)


def config(config_file=None, path=None):
    config_file = config_file or open(os.path.join(
        root(path), '.git', 'config'))

    def get_chunks():
        chunk = []
        for line in config_file:
            line = line.strip()
            if not line:
                continue
            if line.startswith('['):
                if chunk:
                    yield chunk
                chunk = []
            chunk.append(line)
        if chunk:
            yield chunk

    result = {}
    for chunk in get_chunks():
        name_parts = chunk[0][1:-1].split()
        dict_parts = {}
        for part in chunk[1:]:
            k, v = part.split('=')
            dict_parts[k.strip()] = v.strip()
        if len(name_parts) == 1:
            result[name_parts[0]] = dict_parts
        else:
            category, value = name_parts
            result.setdefault(category, {})[value[1:-1]] = dict_parts
    return result


def project(cfg=None):
    cfg = cfg or config()
    name, project = cfg['remote']['origin']['url'].split('/')[-2:]
    return project[:-4]
