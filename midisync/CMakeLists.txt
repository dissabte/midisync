cmake_minimum_required(VERSION 3.0)

set(APP_NAME midisync)

message(STATUS "Processing ${APP_NAME}...")

project(${APP_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_AUTOMOC ON)

if(LINUX)
	add_definitions(-Wall -Werror)
endif(LINUX)

file(GLOB_RECURSE MIDISYNC_INCLUDE_FILES "src/*.h")
file(GLOB_RECURSE MIDISYNC_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE MIDISYNC_QML_FILES "resources/*.qml")

set(MIDISYNC_SOURCES ${MIDISYNC_INCLUDE_FILES} ${MIDISYNC_SOURCE_FILES})

if(NOT SMIDI_FOUND)
	include(../external/smidi.cmake)
endif()

find_package(Qt5Quick)
find_package(Qt5Widgets)

if (Qt5Quick_FOUND AND Qt5Widgets_FOUND)
	qt5_add_resources(UI_RESOURCES "resources/main.qrc")

	# Adding qml files to the IDE project tree, for convenience
	add_custom_target(midiSyncQml SOURCES ${MIDISYNC_QML_FILES})

	# Creating custom target for building qrc, the dependency for main target
	add_custom_target(midiSyncGenerateQRC DEPENDS ${UI_RESOURCES})

	add_executable(${APP_NAME} ${MIDISYNC_SOURCES} ${UI_RESOURCES})

	add_dependencies(${APP_NAME} midiSyncGenerateQRC smidi)

	target_link_libraries(${APP_NAME} Qt5::Quick Qt5::Widgets smidi pthread asound)
else()
	message(WARNING "Qt not found")
endif()

message(STATUS "Processing ${APP_NAME} is done")
