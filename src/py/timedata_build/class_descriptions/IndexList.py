from . List import *

methods = add_methods(
    methods,
    base='index_list',
    )

value_type = 'size_t'
size = 1

sampleclass = 'size_t'
itemclass = 'size_t'
mutableclass='size_t'
itemgetter = ''
classname = 'IndexList'
class_documentation = """A list of array indices.""",
output_file = 'build/genfiles/timedata/signal/IndexList.pyx'
emptyitem='0'
itemmaker=''
