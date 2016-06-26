from timedata_build.util import add_methods

number_type = 'float'
documentation = 'FIXME'

substitutions = dict(
    class_cpp='${name}Cpp',
    class_py='New$name',
    output_file='build/genfiles/timedata/color/New$name.pyx',
    range='$range',
    )

methods = add_methods({}, base='base')
