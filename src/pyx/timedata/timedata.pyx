include "src/pyx/timedata/base/stl.pyx"
include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/modules.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "src/pyx/timedata/signal/convert.pyx"

include "build/genfiles/timedata/signal/combiner.pyx"
include "build/genfiles/timedata/signal/fade.pyx"
#include "build/genfiles/timedata/signal/render3.pyx"
include "build/genfiles/timedata/signal/stripe.pyx"
include "build/genfiles/timedata/genfiles.pyx"

locals().update(
     Combiner=_Combiner,
#     Fade=_FadeImpl,
#     Render3=_Render3Impl,
     Stripe=_Stripe,
     )

_load_colors()
color = _make_module()

print(timestamp())
