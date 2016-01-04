
add_definitions(-DTEST_DIR="${CMAKE_CURRENT_LIST_DIR}")



add_executable(tst_Something tst_Something.cpp)

qt5_use_modules(tst_Something Test Core Qml Gui Quick)

# add_test(NAME tst_Something COMMAND tst_Something)

FILE(GLOB_RECURSE qmlFiles "*.qml")
add_custom_target(qmlFile SOURCES ${qmlFiles})


add_custom_target(uitest tst_Something)


