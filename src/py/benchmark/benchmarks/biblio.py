
def make_data(size):
    return size, size


def benchmarks():
    import os, sys, time
    #width, height = 64, 32
    width, height = 4 * 64, 4 * 32

    try:
        import bibliopixel
        import BiblioPixelAnimations
    except ImportError:
        root = os.path.dirname(os.getcwd())
        sys.path.append(os.path.join(root, 'BiblioPixelAnimations'))
        sys.path.append(os.path.join(root, 'bibliopixel'))

        import bibliopixel
        import BiblioPixelAnimations

    from bibliopixel.drivers.network import DriverNetwork
    from bibliopixel.drivers.dummy_driver import DriverDummy, DriverBase
    from bibliopixel import LEDMatrix, log
    from BiblioPixelAnimations.matrix.bloom import Bloom
    from BiblioPixelAnimations.matrix.circlepop import CirclePop

    def do_circle_pop(size, use_timedata, debug=False):
        debug and log.setLogLevel(log.DEBUG)
        saved_timedata = DriverBase.USE_TIMEDATA
        try:
            driver = DriverDummy(num=width * height, delay=0)
            led = LEDMatrix(driver, width=width, height=height, serpentine=False,
                            threadedUpdate=False)
            anim = CirclePop(led)
            anim.run(max_steps=10, max_cycles=size)
        finally:
            DriverBase.USE_TIMEDATA = saved_timedata
            debug and log.setLogLevel(log.WARNING)

    def circle_pop_timedata(size, _):
        do_circle_pop(size, True, True);

    def circle_pop(size, _):
        do_circle_pop(size, False, True);

    return [('circle_pop', circle_pop),
            ('circle_pop_timedata', circle_pop_timedata)]
