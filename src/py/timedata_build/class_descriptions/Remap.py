from . List import *

methods = add_methods(
    methods,
    base='remap',
    )

value_type = 'size_t'
size = 1

sampleclass = 'size_t'
itemclass = 'size_t'
mutableclass='size_t'
itemgetter = ''
classname = 'Remap'
class_documentation = """Remap one list onto another.""",
output_file = 'build/genfiles/timedata/signal/Remap.pyx'
emptyitem='0'
itemmaker=''
