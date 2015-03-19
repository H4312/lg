# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (LG)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(include)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
#add_subdirectory (include)
#add_subdirectory (src)



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

add_executable(

    lg

    ${source_files}

    ${header_files}

)

install(TARGETS lg DESTINATION bin)