#!/usr/bin/env python3

import tada, timeit

SIZE = 1024

CLASSIC = [0] * (3 * SIZE)
TRIPLES = [(0, 0, 0)] * SIZE

TADA = tada.OperatorTest()
TADA.resize(SIZE)

def operator_add(arg):
    TADA.operator_add(2)

def class_add(arg):
    TADA.class_add(2)

def operator_pow(arg):
    TADA.operator_pow(2)

def class_pow(arg):
    TADA.class_pow(2)

def run(command, arg, number=1000):
    return timeit.Timer(lambda: command(arg)).timeit(number=number)

print('tests')

for arg in 2, TADA:
    print('-->', 'number' if arg == 2 else 'list', '\n')
    for t in 'add', 'pow':
        for s in 'operator', 'class':
            print('%8s %s' % (s, t), 100 * run(locals()['_'.join((s, t))], arg))
