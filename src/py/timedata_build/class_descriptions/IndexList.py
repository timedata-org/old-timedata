from . List import *

methods = add_methods(
    methods,
    base='index_list',
    )

value_type = 'int'
size = 1

sampleclass = 'int'
itemclass = 'int'
mutableclass='int'
itemgetter = ''
classname = 'IndexList'
class_documentation = """A list of array indices.""",
output_file = 'build/genfiles/timedata/signal/IndexList.pyx'
emptyitem='0'
itemmaker=''
