#!/usr/bin/env python3

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

import datetime, importlib, json, os, pathlib, platform, sys, time, timeit

# The format for timestamps and thus filenames.
TIMESTAMP_FORMAT = '%Y%m%d-%H%M%S'

# Suffix for results files.
FILE_SUFFIX = '.json'

# The top level directory, which contains timedata.so.
ROOT = pathlib.Path().resolve().parent.parent.parent

# ROOT must be in sys.path before importing timedata.
sys.path.append(str(ROOT))

import timedata


def write_result(name, **kwds):
    sub = ROOT.joinpath('results', name)
    try:
        sub.mkdir()
    except FileExistsError:
        pass
    timestamp = datetime.datetime.utcnow().strftime(TIMESTAMP_FORMAT)
    filename = str(sub.joinpath(timestamp + FILE_SUFFIX))
    with open(filename, 'w') as fp:
        json.dump(dict(kwds, name=name, timestamp=timestamp), fp, indent=4)


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


def run_benchmarks(args):
    # Read and remove flags.
    size, number = 10240, 200
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
        module = importlib.import_module(name, __name__)
        results = dict()
        for test, function in module.benchmarks():
            data = module.make_data(size)
            timer = timeit.Timer(lambda: function(*data))
            results[test] = timer.timeit(number=number)

        write_result(name, results=results, **metadata)


__all__ = ['lists']


if __name__ == '__main__':
    args = sys.argv[1:] or __all__[:]
    print('Benchmarking', ' '.join(args))
    run_benchmarks(args)
