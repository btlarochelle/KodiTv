set(APP_NAME          KodiTv)
set(APP_ID            "KodiTv.larochelle-brian")
#set(TESTQMLPLUGIN_DIR "share/qml/KodiTv")
#set(MAIN_QML          "Main.qml")
#set(ICON              "graphics/testQmlPlugin.png")

project(APP_NAME C CXX)
cmake_minimum_required( VERSION 3.0.2 )

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(APP_NAME_VERSION_MAJOR 1)
set(APP_NAME_VERSION_MINOR 0)
set(APP_NAME_VERSION_PATCH 6)
set(APP_NAME_Version_String ${APP_NAME_VERSION_MAJOR}.${APP_NAME_VERSION_MINOR}.${APP_NAME_VERSION_PATCH} )


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")


if(${PROJECT_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
   message(FATAL_ERROR "In-tree build attempt detected, aborting. Set your build dir outside your source dir, delete CMakeCache.txt from source root and try again.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# Make sure we have all the needed symbols
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-z,defs")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-z,defs")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-permissive -pedantic -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

include(FindPkgConfig)
find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)
#find_package(Qt5DBus REQUIRED)
#find_package(Qt5Concurrent REQUIRED)
#find_package(Qt5Sql REQUIRED)
#find_package(Qt5Xml REQUIRED)

#include(GNUInstallDirs)
set(HEADERS "" )

# Static C++ checks
#add_custom_target(cppcheck COMMAND cppcheck --enable=all -q --error-exitcode=2  ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/tests)

#enable_testing()

add_subdirectory(backends)
add_subdirectory(src)
add_subdirectory(tests)






