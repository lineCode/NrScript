cmake_minimum_required(VERSION 3.8)
project(NrScript)

set(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_CXX_COMPILER "clang++")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

# 引用头文件路径
include_directories("../../../include")

# 源码路径
set(NRINC "../../../include/NrScript")
set(NRSRC "../../../src/NrScript")

set(SRC_MODULE_BASE
        ${NRINC}/base.h
        ${NRINC}/base/NrSimpleCharT.h
        ${NRINC}/base/NrEvent.h
        ##############################

        ${NRSRC}/base/NrSimpleCharT.cpp
)

set(SRC_MODULE_UI
        #${NRINC}/skia.h
        ${NRINC}/ui.h
        ${NRINC}/ui/utils/NrRect.h
        ${NRINC}/ui/internal/NrWindowBase.h
        ${NRINC}/ui/internal/NrWidgetProperty.h
        ${NRINC}/ui/widgets/NrControl.h
        ${NRINC}/ui/internal/NrWidgetsTreeRenderer.h
        ${NRINC}/ui/NrWindowImpl.h
        ${NRINC}/ui/NrApplication.h

        ${NRINC}/platform/linux/NrWindowImplOSUnix.h
        ${NRINC}/platform/linux/NrApplicationOSUnix.h
        ################################
        ${NRSRC}/ui/internal/NrWindowBase.cpp
        ${NRSRC}/ui/widgets/NrControl.cpp
        ${NRSRC}/ui/internal/NrWidgetsTreeRenderer.cpp
        ${NRSRC}/ui/NrWindowImpl.cpp
        ${NRSRC}/ui/NrApplication.cpp

        ${NRSRC}/platform/linux/NrWindowImplOSUnix.cpp
        ${NRSRC}/platform/linux/NrApplicationOSUnix.cpp
)

add_library(NrScript
        ${NRINC}/defs.h

        ${SRC_MODULE_BASE}
        ${SRC_MODULE_UI})

target_link_libraries(NrScript ${GTK3_LIBRARIES})
add_definitions(-DNRSCRIPT_EXPORTS -DNRSCRIPT_BUILD_PLATFORM_LINUX)