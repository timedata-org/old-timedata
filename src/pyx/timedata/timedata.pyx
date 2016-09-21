include "src/pyx/timedata/base/stl.pyx"
include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/modules.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "src/pyx/timedata/signal/convert.pyx"

include "build/genfiles/timedata/genfiles.pyx"
include "src/pyx/timedata/signal/renderer.pyx"

locals().update(**_make_module())

print_startup_message()
