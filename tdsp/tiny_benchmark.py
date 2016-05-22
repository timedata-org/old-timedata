#!/usr/bin/env python3

import tdsp, timeit

SIZE = 1024

CLASSIC = [0] * (3 * SIZE)
TRIPLES = [(0, 0, 0)] * SIZE

TDSP = tdsp.OperatorTest()
TDSP.resize(SIZE)

def operator_add(arg):
    TDSP.operator_add(2)

def class_add(arg):
    TDSP.class_add(2)

def operator_pow(arg):
    TDSP.operator_pow(2)

def class_pow(arg):
    TDSP.class_pow(2)

def run(command, arg, number=1000):
    return timeit.Timer(lambda: command(arg)).timeit(number=number)

print('tests')

for arg in 2, TDSP:
    print('-->', 'number' if arg == 2 else 'list', '\n')
    for t in 'add', 'pow':
        for s in 'operator', 'class':
            print('%8s %s' % (s, t), 100 * run(locals()['_'.join((s, t))], arg))
