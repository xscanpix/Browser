project(LibJS)

set(LIBJS_INCLUDE_DIRECTORY
  .
)

set(LIBJS_SRCS
  "LibJS/Token.h"
  "LibJS/Token.cpp"
  "LibJS/Lexer.h"
  "LibJS/Lexer.cpp"
  "LibJS/Source.h"
  "LibJS/Source.cpp"
)

add_library(LibJS SHARED
  ${LIBJS_SRCS}
)

set_target_properties(LibJS
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    LINKER_LANGUAGE CXX
)

target_link_libraries(LibJS LibBase)

target_include_directories(LibJS PUBLIC
  ${LIBJS_INCLUDE_DIRECTORY}
)
