### timedata - time arts data. ###

High-performance color arithmetic for C++ and Python.


## Why? ##

Controlling colored lights requires a great deal of arithmetic and this is too
slow in Python to get either very high frame rates, or complex patterns with
more than a few components - particularly on small machines like the Raspberry
Pi.

Traditional color arithmetic is done in 8-bit integers, which provide inadequate
resolution for smooth fades - particularly when everything is gamma corrected
(exponentiated) at the very last step.

## What do you get? ##

_timedata_ provides two main Python classes: `Color` and `ColorList`. (It also
provides a generic C++ library, a bunch of unit tests in C++ and even more unit
tests in Python, if that's the sort of thing you like.)

`Color` looks very much like a Python `tuple` with three elements containing
floating point numbers - except it takes a little over half as much memory, can
be constructed from a human readable string description like `"red"` or
`"gray 33.3"` and has a large number of color-appropriate operations.

`ColorList` looks very much like a Python `list` of `Color` - except that it
takes rougly 25% of the memory of a `list` of `tuple` and performs common color
operations anywhere from 10 to over 100 times as fast.

These two main classes come in two flavors.  `Color` and `ColorList` are
_normalized_ - their color components (red, green or blue) are expected to be
between 0 and 1.

For legacy systems, `Color256` and `ColorList256` offer the same features except
that the color components are expected to be between 0 and 255.

(Note the use of the word "expected".  _timedata_ does not bar color components that
are out of range in intermediate calculations!  Components can be large, they
can even be negative, and _timedata_ will try to do a reasonable job.  Of course, at
the very last step, these "extended colors" will need to be rendered into a
visible color palette, and even then you can choose how to handle "out of band"
colors.)

_timedata_ is optimized first for correctness of course, but then strongly for
speed.  In particular, it's easy to organize real-time projects so that no
memory allocation can occur on a frame update, and no locks are held.


## FAQ and chat ##

1. How do I write high-performance code?  How do I write thread-safe code
   without locks?

At this time, you can't actually run _timedata_ without any locks.  By default,
Python's own GIL is locked every time you call anything in _timedata_ - like most of
Python's structures - so you'd have to work reasonably hard to shoot yourself in
the foot.

Locking the GIL is bad.  It more or less shuts down any other threads in your
Python program while it's held.

Quite soon there will be new flavors of the main classes which do _not_ lock the
GIL.  You'll provide a frame rendering callback which will be called at a point
where you can manipulate all the `ColorList`s without locks.

If you have other threads doing sequencing or real-time data gathering, you will
have to communicate with this frame rendering callback with a thread-safe queue,
which is provided - and won't be a big deal for you to use.

2. Why not use numpy?

numpy is a system that provides fast vector and matrix arithmetic for Python -
seemingly tailor-made for this project.

The initial plan was numpy, but this was abandoned for three reasons - raw
speed, resource management, and features.

2.1. Raw speed.

Even though numpy is a rough order of magnitude faster than Python, in
admittedly limited benchmarks, _timedata_ outperformed numpy by half an order of
magnitude yet again.

The reason is specificity. In C++, _timedata_ looks like a lot of generic, templated
code - so at code generation time, the compiler knows, for example, that colors
have three components and can unroll any loops it wants to.

In numpy, arrays have many properties, all of which need to be resolved before
you can actually do your arithmetic.

And this costs you.

In _timedata_ you can see all these
[repetitive code](https://github.com/rec/timedata/blob/master/src/timedata/color/colorList_inl.h#L104-L210).
When I introduced _one_ level of indirection here - just a single integer to
look up the operation to do - I lost between 4% and _40%_ of my performance on
common numerical tasks!

2.2. Resource management.

numpy does have a lot of mutators, but it's primarily focused on being
function - returning new values.  Many functions by now do have the ability to
pass in an existing array to mutate into, but then things are poorly defined if
that array is also the source, and again - layers of indirection are not free.

In _timedata_, mutators - that means, things that change the state of a
`ColorList` - are the preferred way to go.  The reason is simple - memory
management!  Every time you create a new Python object, and to a lesser extent
each time you even create a new C++ vector, you're manipulating your heap, your
central source of memory allocations.

It's not just that heap operations aren't cheap - it's that if you are doing
these operations in real-time, when you are in a hurry, you just don't know how
long they will take!  If you're requesting a chunk of memory from the heap,
sometimes the program will stall for a few milliseconds... resulting in jitter
or in the case of a DAC drop-outs or even noise.

_timedata_'s `ColorList` is built around mutators.  For each operation that creates
a new list - like `+` - there's an equivalent operation that mutates the list -
like `+=`.  And there are many useful operations that exist only in mutator form
(*).

On the flip side, `Color` has _no_ mutators.  `Color` is extremely light,
costing just 40 bytes (as compared to a Python triple at 72 bytes) so it's
cheaper and easier to make a new one for each operation.

And it's really convenient from the point of view of a user - you can just use a
`Color` like a string or a number, and never worry about thread-safety or side
effects.


2.3. Features.

Having an API that understands color is really handy!

    c = (Colors.red + Colors.blue)
    cl = ColorList([c] * 3 + [Colors.yellow] * 5
    cl += ColorList.spread(Colors.white, Colors.black, 10)
    c2 = cl.rgb_to_hsv()


3. What's the roadmap?

This project is part of a larger project to provide generic, high-speed
processing in C++ and Python for _all_ time arts data - thus the name _timedata_.

This first phase centered on providing fast routines to do color processing
because these were sorely lacking, and because of the author's own immediate
need for fast color arithmetic for LED control.

This is now more or less complete, though a bit of clean-up is going on.

3.1. Back to C++ for a while!

While from the C++ end this was originally written to process _any_ sort of
time-based signal, after that design period there was a deliberate goal to produce
a mature Python library just for color arithmetic.  This resulted in a great
deal of code being generated that is specific just to colors.

I expect almost all of that code will be usable for other domains of time arts
data - audio sample data; MIDI, OSC, CV or other controller data; DMX; ILDA; etc
etc.

So the next step is to go back, preserving all the Python end, and pull the C++
back up to be more general and less color focused.


3.2. Dealing with more types of Color.

We aren't dealing with RGB vs HSV very well yet.

And what about transparency (alpha)?

Modern lighting strings have more complex color models - with new colors like
"amber" and "ultraviolet".

And what about color models in general?

And how do we extend that to other sorts of lights without any sort of component
model at all - like DMX or ILDA?

The C++ generic formulation does handle this perfectly well _but_ representing
that in Cython will be challenging, as Cython is known not to handle this
problem well.

It might well be that more template writing code will need to be created!


---

(* - As a convenience, all these functions return a pointer to `self`, so you
can chain them exactly as if they returned a new value - like

    colors.invert().max_limit(0.8).min_limit(0.2)
)
