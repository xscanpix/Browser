project(LibBase)

set(LIBBASE_INCLUDE_DIRECTORY
  "."
)

set(LIBBASE_SRCS
  "LibBase/Base.h"
)

add_library(LibBase SHARED
  ${LIBBASE_SRCS}
)

set_target_properties(LibBase
  PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(LibBase PUBLIC
  ${LIBBASE_INCLUDE_DIRECTORY}
)