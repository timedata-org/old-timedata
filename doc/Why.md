Why `timedata`?
=========

* What are we trying to accomplish?

`timedata` represents models of time data - collections of data which vary over
time.  Our initial exploration is restricted to the field of colors.

Our two goals are to be able to represent any color model - there are dozens! -
and to be able to do as accurately and efficiently as possible.

The result is a collection of Python classes named `Color` and `ColorList` that
represent long strings of floating point color pixels close-packed in memory,
and which provide lots of high-performance arithmetic and other convenient and
powerful functionality.


* Why not pure Python?

Controlling colored lights requires a great deal of arithmetic and this is too
slow in Python to get either very high frame rates, or complex patterns with
more than a few components - particularly on small machines like the Raspberry
Pi.

Traditional color arithmetic is done in 8-bit integers, which provide inadequate
resolution for smooth fades - particularly when everything is gamma corrected
(exponentiated) at the very last step.


* Why not use numpy?

We explored using the excellent Python high-performance vector and matrix
arithmetic package for this purpose.  We were immediately able to get half order
of magnitude improvement in frame rates.

But there were immediate issues.  In order to handle multiple models, there
needed to be a lookup at each computation.  Frame rates suffered.   Dropping in
C++ methods or functions to perform model conversion proved problematic.  Gamma
computation was surprisingly slow - using a table seemed to involve another
(slow) trip through Python.

To get best performance, we needed to be able to cut out all the levels of
indirection.  `numpy` wasn't going to get us there.


* Why generic code?

Python has the concept of
[duck typing](https://en.wikipedia.org/wiki/Duck_typing), where you call methods
by name at runtime rather than relying on having a specific interface.

In C++, the concept is a little different.  Generic C++ code is _templated_
code, code where one or more _classes_ are variable - and these substitutions
happen at compilation time, not at runtime.

In many ways, this is the best of all possible worlds.  The compiler knows
exactly what the type of the class is at compilation time, and can often make
huge optimizations while it is generating the code - at the cost of an
executable that's a tiny bit larger, which is basically "for free".

Think of this as "the power of indirection, without the runtime cost".


* Why all the .pyx/Cython templates and generated code?

It became very quickly clear that there were going to be a huge number of
variations:

* three base classes
  * `MutableColor`
  * `Color`
  * `ColorList`
  * (we're likely going to change these to `Color`, `ColorConst`, `ColorList`)

* half a dozen color models now and easily dozens later
  * HSL
  * HSV
  * RGB
  * XYZ
  * YIQ
  * YUV

* ranges
  * normalized: [0, 1]
  * 8-bit: [0, 255]
  * 8-bit corrected: [0, 256]

* component counts that aren't 3
  * mono
  * new components: Amber, Ultraviolet, White, Lime are all colors in existing LED chips.

Now, not all possibilities are realized - the alternate ranges are
only provided for the RGB color model, and everything else is normalized;  and
right now, all models have three components.  But this still results in 24
separate classes.

We could easily cut that down using inheritance - at the cost of a bunch of
lookups.

But maintaining 24 classes now and some indefinite number later seems
impossible.  Instead, it was decided to make a machine to manufacture Cython
classes - the files with the .pyx ending you see in the generated code.

Now to add a new class, you just need to add a new C++ model and add an entry in
a table.  You can also build the whole system with a very small number of
classes and color models for testing - which very much improves the iteration
speed.
