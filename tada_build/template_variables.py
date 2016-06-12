#!/usr/bin/env python3

import re, sys

findall = re.compile(r'\{([^}]+)\}').findall

# List the template variables in a section of code.

def template_variables(files):
    result = set()
    for f in files:
        for i in open(f):
            for j in findall(i):
                j.startswith('{') or result.add(j)
    return result

if __name__ == '__main__':
    for t in sorted(template_variables(sys.argv[1:])):
        print(t)
