TEMP_LOG = print

include "src/pyx/timedata/base/stl.pyx"
include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/modules.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "src/pyx/timedata/signal/convert.pyx"

include "build/genfiles/timedata/genfiles.pyx"

locals().update(Render3=_Render3, **_make_module())

include "src/pyx/timedata/signal/renderer.pyx"

del TEMP_LOG

print_startup_message()
