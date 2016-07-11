import collections, numbers, sys

def getsize(obj):
    # Adapted from https://stackoverflow.com/questions/449560
    nothing = object()
    seen_ids = set([nothing])

    """Recursively iterate to sum size of object & members."""
    def inner(obj):
        obj_id = id(obj)
        if obj_id in seen_ids:
            return 0
        seen_ids.add(obj_id)
        size = sys.getsizeof(obj)
        if isinstance(obj, (str, bytes, numbers.Number, range, bytearray)):
            return size

        if isinstance(obj, (tuple, list, collections.Set, collections.deque)):
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
