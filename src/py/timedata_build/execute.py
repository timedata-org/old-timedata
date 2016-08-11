import platform, subprocess


def run(*cmds):
    return subprocess.check_output(cmds).strip().decode('ascii')


def git_tags():
    if platform.system() == 'Windows':
        return 'windows'

    tags = run('git', 'describe', '--tags', '--always')
    branch = run('git', 'rev-parse', '--abbrev-ref', 'HEAD')
    remote = run('git', 'config', 'remote.origin.url')
    user = remote.split(':')[1].split('/')[0]
    return '%s+%s.%s' % (tags, branch, user)


def git_push(path, message):
    dot = os.path.abspath('.')
    os.chdir(path)
    try :
        return (run('git', 'add', '--all', '.'),
                run('git', 'commit', '-am', '"%s"' % message),
                run('git', 'push'))
    finally:
        os.chdir(dot)
