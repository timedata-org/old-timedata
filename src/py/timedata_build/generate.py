import os


def generate(structs, tiny, models, outfile, template_directory):
    filenames = list()

    for c in read_classes.read_classes(tiny=tiny, models=models):
        filenames.append(write_class.write_class(
            c.methods, template_directory=template_directory, **c.__dict__))

    data = ''.join('include "%s"\n' % f for f in sorted(filenames))
    files.write_if_different(outfile, data)
