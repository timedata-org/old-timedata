def split_files(files):
    return {pathlib.Path(f).stem: split(open(str(f)), f) for f in files}

def pretty_split(parts):
    for name, d in sorted(parts.items()):
        for action, value in sorted(d.items()):
            print('%s: %s:' % (action, name))
            print(value)

def combine_globs(args):
    files = []
    p = pathlib.Path('.')
    for a in args:
        files.extend(p.glob(a))
    return files

def split_globs(args):
    return split_files(combine_globs(args))

def template_variables(files):
    """List the template variables in a section of code."""
    findall = re.compile(r'\{([^}]+)\}').findall
    result = set()
    for f in files:
        for i in open(f):
            for j in findall(i):
                j.startswith('{') or result.add(j)
    return result
