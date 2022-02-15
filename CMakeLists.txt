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

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/ea55f1f52c489535f0d3b583c81529762c9cb5ea.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  tests/LibJS/TestLexer.cpp
)
target_link_libraries(
  hello_test
  gtest_main
  LibJS
)

include(GoogleTest)
gtest_discover_tests(hello_test)