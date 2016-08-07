
def make_data(size):
    return size, size


def benchmarks():
    import os, sys, time

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
    from bibliopixel.drivers.dummy_driver import DriverDummy
    from bibliopixel import LEDMatrix, log
    from BiblioPixelAnimations.matrix.bloom import Bloom
    from BiblioPixelAnimations.matrix.circlepop import CirclePop

    def circle_pop(size, _):
        driver = DriverDummy(num=64 * 32, delay=0)
        led = LEDMatrix(driver, width=64, height=32, serpentine=False,
                        threadedUpdate=False)
        anim = CirclePop(led)
        anim.run(max_steps=10, max_cycles=size)
    return [('circle_pop', circle_pop)]
