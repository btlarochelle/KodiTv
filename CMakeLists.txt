project(KodiTv)
cmake_minimum_required( VERSION 2.8.11 )

set(APP_NAME          KodiTv)
set(APP_ID            "KodiTv.larochelle-brian")
#set(TESTQMLPLUGIN_DIR "share/qml/KodiTv")
#set(MAIN_QML          "Main.qml")
#set(ICON              "graphics/testQmlPlugin.png")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Static C++ checks
#add_custom_target(cppcheck COMMAND cppcheck --enable=all -q --error-exitcode=2
#                  ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/tests)

find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Test REQUIRED)

set(INCLUDE ${CMAKE_SOURCE_DIR}/src/backendplugininterface.h )

#add_custom_target(run COMMAND ${CMAKE_BINARY_DIR}/install/KodiTv )

enable_testing()

add_subdirectory(backends)
add_subdirectory(src)
add_subdirectory(tests)



#include(CTest)
#enable_testing()
#set(TEST_LINK_LIBRARIES Qt5::Test)
#add_subdirectory(tests)




