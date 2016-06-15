cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing unittests...")

set(MIDISYNC_TESTS midisync_tests)

include_directories(${UNITTEST_CPP_DIR})

file(GLOB MIDISYNC_TESTS_INCLUDE_FILES "*.h")
file(GLOB MIDISYNC_TESTS_SOURCE_FILES "*.cpp")

set(MIDISYNC_TESTS_SOURCES ${MIDISYNC_TESTS_INCLUDE_FILES} ${MIDISYNC_TESTS_SOURCE_FILES})

add_executable(${MIDISYNC_TESTS} ${MIDISYNC_TESTS_SOURCES})

target_link_libraries(${MIDISYNC_TESTS} UnitTest++ smidi)

message(STATUS "Processing unittests done")
