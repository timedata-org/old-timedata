#!/usr/bin/env python3

import tdsp, timeit

SIZE = 1024

CLASSIC = [0] * (3 * SIZE)
TRIPLES = [(0, 0, 0)] * SIZE
TDSP = tdsp.ColorList()
TDSP.resize(SIZE)

def scale_functional(colors):
    return [c * 2 for c in colors]

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
print('func:   ', run(scale_functional, CLASSIC))
print('classic:', run(scale_classic, CLASSIC))
print('triples:', run(scale_triples, TRIPLES))
print('tdsp:   ', run(scale_tdsp, TDSP))

def gamma_classic(colors):
    for i in range(len(colors)):
        colors[i] **= 1.2

def gamma_triples(colors):
    for i, c in enumerate(colors):
        r, g, b = c
        colors[i] = (r ** 1.2, g ** 1.2, g ** 1.2)

def gamma_tdsp(colors):
    colors **= 1.2

# From https://github.com/scottjgibson/PixelPi/blob/master/pixelpi.py
LPD8806 = [int(pow(float(i) / 255.0, 2.5) * 255.0 + 0.5) for i in range(256)]
APA102 = LPD8806
WS2801 = [int(pow(float(i) / 255.0, 2.5) * 255.0) for i in range(256)]
SM16716 = [int(pow(float(i) / 255.0, 2.5) * 255.0) for i in range(256)]

# From http://rgb-123.com/ws2812-color-output/
WS2812B = NEOPIXEL = WS2812 = [int(pow(float(i) / 255.0, 1.0 / 0.45) * 255.0) for i in range(256)]

def gamma_classic_table(colors):
    for i in range(len(colors)):
        colors[i] = LPD8806[colors[i]]


print('\n\ngamma\n')
print('classic:      ', run(gamma_classic, CLASSIC))

CLASSIC = [int(c) for c in CLASSIC] # clear it out!
print('classic table:', run(gamma_classic_table, CLASSIC))
print('triples:      ', run(gamma_triples, TRIPLES))
print('tdsp:         ', run(gamma_tdsp, TDSP))
