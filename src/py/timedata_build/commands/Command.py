from .. context import CONFIG
from .. arguments import FLAGS

from setuptools import Command as _Command

class Command(_Command):
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass
