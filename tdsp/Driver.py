import tdsp

import itertools

class Driver(object):
    PERMUTATIONS = tuple(itertools.permutations('rgb'))
    PARAMS = 'brightness', 'gamma', 'max', 'min', 'permutation'

    BRIGHTNESS = 1.0
    GAMMA = 1.0
    MAX = 255
    MIN = 0
    PERMUTATION = 0

    def __init__(self, size, renderer=tdsp.Renderer, **kwds):
        unknown = set(kwds) - set(PARAMS)
        if unknown:
            raise ValueError('Unknown keywords: ' + ''.join(unknown))

        self._size = size
        self._header = bytearray(self.header(), encoding='ascii')
        footer = bytearray(self.footer(), encoding='ascii')
        self._message = self._header + bytearray(self._body_size()) + footer
        self.model = renderer(size, self._message, len(self._header))
        for p in self.PARAMS:
            setattr(self.model, p, kwds.get(p, getattr(self, p.upper())))

    def _body_size(self):
        # Override for non-RGB, etc.
        return 3 * self._size
