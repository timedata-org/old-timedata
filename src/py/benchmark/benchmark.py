"""
Common functions for computing and reporting benchmarks.

What do we need to know when reporting a test?
  results/ (directory)
    <timestamp>.json (file containing json named after the timestamp)
      machine info:  (a dict)
      compilation flags (string)
      size:  (number of "items" in the test)
      results:
         test name: test result
         ...
"""

import collections, datetime, importlib, json, os, pathlib, platform, sys
import time, timeit

from . import lists

# The format for timestamps and thus filenames.
TIMESTAMP_FORMAT = '%Y%m%d-%H%M%S'

# Suffix for results files.
FILE_SUFFIX = '.json'

# The top level directory, which contains timedata.so.
ROOT = pathlib.Path().resolve()

# ROOT must be in sys.path before importing timedata.
sys.path.append(str(ROOT))

import timedata


def sorted_dict(**kwds):
    return collections.OrderedDict(sorted(kwds.items()))


def write_result(name, filename_suffix, **kwds):
    now = datetime.datetime.now()
    date = now.strftime('%Y%m%d')
    time = now.strftime('%H%M%S')
    sub = ROOT.joinpath('results', name, date)
    try:
        sub.mkdir(parents=True)
    except FileExistsError:
        pass
    filename = str(sub.joinpath(time))
    if filename_suffix:
        filename += ('-' + filename_suffix)

    d = sorted_dict(name=name, timestamp=now.isoformat(), **kwds)
    with open(filename + FILE_SUFFIX, 'w') as fp:
        json.dump(d, fp, indent=4)


def version():
    system = platform.system()
    if system == 'Darwin':
       return platform.mac_ver()[0]
    if system == 'Linux':
       return platform.linux_distribution()
    if system == 'Windows':
       return platform.win32_ver()
    print('unknown platform', system)
    return (platform.version(), '', '')


def run_benchmarks(args, filename_suffix, size, number):
    # Read and remove flags.
    for arg in args:
        if arg.startswith('--'):
            name, value = arg.split('=', 1)
            if name == '--size':
                size = int(value)
            elif name == '--number':
                number = int(value)
            else:
                raise ValueError('Bad flag ' + name)
    args = [a for a in args if not a.startswith('--')]

    metadata = dict(
        size=size,
        number=number,
        optimization_flags=timedata.optimization_flags(),
        git_tags=timedata.git_tags(),
        platform=dict(
            system=platform.system(),
            version=version(),
            ),
        )

    for name in args:
        try:
            module = globals()[name]
        except:
            print(sys.path)
            raise
        results = dict()
        for test, function in module.benchmarks():
            data = module.make_data(size)
            timer = timeit.Timer(lambda: function(*data))
            results[test] = timer.timeit(number=number)

        write_result(name, filename_suffix,
                     results=sorted_dict(**results), **metadata)
