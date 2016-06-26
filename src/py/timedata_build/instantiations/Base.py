from timedata_build.util import add_methods

number_type = 'float'
documentation = 'FIXME'

substitutions = dict(
    class_cpp = '${class_py}Cpp',
    class_py='New$class_py',
    output_file='build/genfiles/timedata/color/New$class_py.pyx',
    range='$range',
    )

methods = add_methods({}, base='base')
