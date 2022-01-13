cmake_minimum_required(VERSION 3.18)

project(algodata)
include_directories(include)
add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git)
FetchContent_MakeAvailable(fmt)

add_executable(tests
    "tests/main.cpp")
target_link_libraries(tests fmt::fmt)
