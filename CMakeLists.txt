# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (LG)
enable_testing()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")


# Check for CppUTest and bail out if they don't have it
#if(DEFINED ENV{CPPUTEST_HOME})
#  message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
#else()
#  message("CPPUTEST_HOME is not set; You must tell CMake where to find CppUTest")
#  return()
#endif()


include_directories(include)
add_subdirectory(test)
add_subdirectory(res)


file(
    GLOB_RECURSE

    source_files

    src/*
)

file(
    GLOB_RECURSE

    header_files

    include/*
)

file(
    GLOB_RECURSE

    test_files

    test/*
)

add_executable(

    lg

    ${source_files}

    ${header_files}

    main.cpp

)

add_executable(

    testsuite

    ${source_files}

    ${header_files}

    ${test_files}

)

target_link_libraries(testsuite CppUTest)

install(TARGETS lg DESTINATION bin)