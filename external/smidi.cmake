cmake_minimum_required(VERSION 3.0)

set(SMIDI_ROOT "${CMAKE_SOURCE_DIR}/../external/smidi/smidi")

if(EXISTS ${SMIDI_ROOT}/CMakeLists.txt)
	set(SMIDI_FOUND ON)
	add_subdirectory(${SMIDI_ROOT} smidi)
else()
	message(FATAL_ERROR "Couldn't found smidi's cmake config. Please update smidi submodule.")
endif()
