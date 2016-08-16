import os, shutil, stat
from distutils import dir_util

def copy_tree(f, g):
    return dir_util.copy_tree(os.path.abspath(f), os.path.abspath(g))


def make_writable(f, is_writable=True):
    if os.path.isfile(f):
        try:
            os.chmod(f, stat.S_IWRITE if is_writable else stat.S_IREAD)
        except:
            raise OSError('Failed to change writability for', f)


def splitall(path):
    result = []
    last_path = '/'
    while path and path != last_path:
        last_path = path
        path, part = os.path.split(path)
        result.insert(0, part)
    return result


def clean_dir(*path):
    dname = os.path.join(*path)
    shutil.rmtree(dname, ignore_errors=True)
    os.makedirs(dname)
    return dname


def write_if_different(fname, data):
    """Writes a file if it is different from what's there, creating its
       directory if necessary."""
    try:
        old_data = open(fname).read()
    except:
        old_data = None
    if old_data != data:
        os.makedirs(os.path.dirname(fname), exist_ok=True)
        make_writable(fname)
        open(fname, 'w').write(data)
        make_writable(fname, False)
        print(fname, 'written.')
    else:
        print(fname, 'unchanged.')
