cmake_minimum_required(VERSION 3.0)

set(HOTPLUG_ROOT "${CMAKE_SOURCE_DIR}/../../hotplug/hotplug")

if(EXISTS ${HOTPLUG_ROOT}/CMakeLists.txt)
	set(HOTPLUG_FOUND ON)
	add_subdirectory(${HOTPLUG_ROOT} hotplug)
else()
	message(FATAL_ERROR "Couldn't found hotplug's cmake config. Please update hotplug submodule.")
endif()
