from timedata_build.util import add_methods

number_type = 'float'
documentation = 'FIXME'

substitutions = dict(
    classname='$name',
    output_file='build/genfiles/timedata/color/$name.pyx',
    range='$range',
    )

methods = add_methods({}, base='base')
