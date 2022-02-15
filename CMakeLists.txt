cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_BUILD_TYPE
  Debug
)

set(BROWSER_SRCS
  "test.cpp"
)

project(Browser)

add_subdirectory(src/LibBase)
add_subdirectory(src/LibJS)

add_executable(Browser
  ${BROWSER_SRCS}
)

target_compile_options(Browser PRIVATE -O3 -std=c++17 -Werror -Wall -Wextra -pedantic-errors -Wsign-conversion -Wconversion)

target_link_libraries(Browser LibBase LibJS)