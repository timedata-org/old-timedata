import abc, tdsp

import itertools

class Driver(object):
    __metaclass__ = abc.ABCMeta

    PERMUTATIONS = tuple(itertools.permutations('rgb'))

    # The list of parameter that you're setting on
    PARAMS = 'brightness', 'gamma', 'max', 'min', 'permutation'

    BRIGHTNESS = 1.0
    GAMMA = 1.0
    MAX = 255
    MIN = 0
    PERMUTATION = 0
    RENDERER = tdsp.Renderer

    def __init__(self, size, renderer=None, **kwds):
        unknown = set(kwds) - set(self.PARAMS)
        if unknown:
            raise ValueError('Unknown keywords: ' + ''.join(unknown))

        self.size = size
        self.header = bytearray(self.header(), encoding='ascii')
        self.renderer = (renderer or self.RENDERER)(self)
        self.footer = bytearray(self.footer(), encoding='ascii')
        self.message = (
            self.header + bytearray(self.renderer.byte_size) + self.footer)
        self.renderer.set_message(self.message)

        for p in self.PARAMS:
            setattr(self.renderer, p, kwds.get(p, getattr(self, p.upper())))

        # If we don't have a render method, use the one from the renderer.
        self.render = getattr(self, 'render', self.renderer.render)

    def _body_size(self):
        # Override for non-RGB, etc.
        return 3 * self._size

    @abc.abstractmethod
    def header(self):
        """Return a string with the header of the message, before the lights."""
        return

    @abc.abstractmethod
    def footer(self):
        """Return a string with the footer of the message, after the lights."""
        return
