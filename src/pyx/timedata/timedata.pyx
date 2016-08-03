include "src/pyx/timedata/base/stl.pyx"
include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/modules.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "src/pyx/timedata/signal/convert.pyx"

include "build/genfiles/timedata/genfiles.pyx"

locals().update(
     Combiner=_Combiner,
     Fade=_Fade,
     Render3=_Render3,
     Stripe=_Stripe,
     **_make_module())

include "src/pyx/timedata/signal/renderer.pyx"

print_startup_message()
