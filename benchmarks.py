#!/usr/bin/env python3

import tdsp, timeit

SIZE = 1024

CLASSIC = [0] * (3 * SIZE)
TRIPLES = [(0, 0, 0)] * SIZE
TDSP = tdsp.ColorList()
TDSP.resize(SIZE)

def scale_classic(colors):
    for i in range(len(colors)):
        colors[i] *= 2

def scale_triples(colors):
    for i, c in enumerate(colors):
        r, g, b = c
        colors[i] = (2 * r, 2 * g, 2 * b)

def scale_tdsp(colors):
    colors *= 2

def run(command, value, number=1000):
    return timeit.Timer(lambda: command(value)).timeit(number=number)

print('scale\n')
print('classic', run(scale_classic, CLASSIC))
print('triples', run(scale_triples, TRIPLES))
print('tdsp', run(scale_tdsp, TDSP))

def gamma_classic(colors):
    for i in range(len(colors)):
        colors[i] **= 1.2

def gamma_triples(colors):
    for i, c in enumerate(colors):
        r, g, b = c
        colors[i] = (r ** 1.2, g ** 1.2, g ** 1.2)

def gamma_tdsp(colors):
    colors **= 1.2

print('\n\ngamma\n')
print('classic', run(gamma_classic, CLASSIC))
print('triples', run(gamma_triples, TRIPLES))
print('tdsp', run(gamma_tdsp, TDSP))
