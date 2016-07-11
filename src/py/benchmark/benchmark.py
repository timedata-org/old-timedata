#!/usr/bin/env python3

"""Common functions for computing and reporting benchmarks."""

import pathlib, sys

# The top level directory containing timedata.so
ROOT = str(pathlib.Path().resolve().parent.parent.parent)

if ROOT not in sys.path:
    sys.path.append(ROOT)

# From https://stackoverflow.com/questions/449560

import sys

from numbers import Number
from collections import Set, Mapping, deque

def getsize(obj):
    nothing = object()
    seen_ids = set([nothing])

    """Recursively iterate to sum size of object & members."""
    def inner(obj):
        obj_id = id(obj)
        if obj_id in seen_ids:
            return 0
        seen_ids.add(obj_id)
        size = sys.getsizeof(obj)
        if isinstance(obj, (str, bytes, Number, range, bytearray)):
            return size

        if isinstance(obj, (tuple, list, Set, deque)):
            return size + sum(inner(i) for i in obj)

        if hasattr(obj, 'items'):
            return size + sum(inner(k) + inner(v) for k, v in obj.items())

        if hasattr(obj, '__slots__'):
            # Must be custom object instances.
            slots = (getattr(obj, s, nothing) for s in obj.__slots__)
            return size + sum(inner(s) for s in slots)

        # Must be an object.
        return size + inner(getattr(obj, '__dict__', nothing))

    return inner(obj)
