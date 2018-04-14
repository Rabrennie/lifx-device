cmake_minimum_required(VERSION 2.6)
add_definitions(-Wfatal-errors)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
include_directories (include)
file(GLOB SOURCES "**/*.cpp")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)