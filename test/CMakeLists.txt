project (LG)

## include project source
#include_directories(${PROJECT_SOURCE_DIR}/../include)
#
#
## include mocks only for test code
#include_directories(${PROJECT_SOURCE_DIR}/../mocks)
#
## include CppUTest headers
#include_directories($ENV{CPPUTEST_HOME}/include)
#
## add cpputest library
#add_library(imp_cpputest STATIC IMPORTED)
#set_property(TARGET imp_cpputest PROPERTY
#             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/lib/libCppUTest.a)
#
#
#add_executable(RunAllTests MainTestSuite.cpp)
#target_link_libraries(RunAllTests imp_cpputest RuntimeErrorStub)