cmake_minimum_required(VERSION 3.0.0)
project(btageffanalyzer)

# Include src
include_directories(src)

# Dependencies
include_directories(include)

# Tests
macro(add_test testname)
    add_executable(${testname}.o tests/${testname}.cc)
endmacro(add_test)

# Examples
macro(add_example testname)
    add_executable(${testname}.o examples/${testname}.cc)
endmacro(add_example)

add_example(main examples/main.cc)
add_test(missing tests/missing.cc)
add_test(performance tests/performance.cc)