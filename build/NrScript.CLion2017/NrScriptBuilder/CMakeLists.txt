cmake_minimum_required(VERSION 3.9)
project(NrScriptBuilder)

set(CMAKE_CXX_STANDARD 17)
set(SKIA_BUILD_FOR linux)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

include_directories("../../../include")
link_directories("../../../output/Linux/NrScript/x64/debug")
set(NRDIR "../../../NrScriptBuilder")

#
# Gtk+-3 include
#

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(NrScriptBuilder
        ${NRDIR}/NrBuilderApp.h
        ${NRDIR}/NrBuilderFrame.h

        ${NRDIR}/NrBuilderApp.cpp
        ${NRDIR}/NrBuilderFrame.cpp
        ${NRDIR}/GtkMain.cpp)

target_link_libraries(NrScriptBuilder NrScript)
target_link_libraries(NrScriptBuilder ${GTK3_LIBRARIES})
add_definitions(-DNRSCRIPT_BUILD_PLATFORM_LINUX)