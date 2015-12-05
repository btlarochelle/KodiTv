project(KodiTv)
cmake_minimum_required( VERSION 2.8.11 )

set(APP_NAME          testQmlPlugin)
set(APP_ID            "testqmlplugin.larochelle-brian")
set(TESTQMLPLUGIN_DIR "share/qml/testQmlPlugin")
set(MAIN_QML          "Main.qml")
set(ICON              "graphics/testQmlPlugin.png")


set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)

set(INCLUDE src/backendplugininterface.h ) 

add_subdirectory(backends)
add_subdirectory(src)



#add_executable(${PROJECT_NAME} ${INCLUDE} ${SOURCES} ${SRC_LIST})
#add_library( cmakePlugin SHARED cmakeplugin.cpp )





