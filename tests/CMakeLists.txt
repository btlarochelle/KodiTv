

# add_custom_target(unittests)

#add_executable(unittests testplugintest.cpp)
#add_test(foo foo)

#qt5_use_modules(${util_test}TestExec Test Core Qml)
#target_link_libraries(testplugintest.cpp Qt5::Test)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
#set(testplugintest_SRCS testplugintest.cpp)
#ADD_EXECUTABLE( TestPluginTest ${testplugintest_SRCS} )
#TARGET_LINK_LIBRARIES( TestPluginTest ${TEST_LIBRARIES} )
#ADD_TEST( NAME TestPluginTest COMMAND TestPluginTest )
#qt5_use_modules(TestPluginTest Test Core)

ADD_EXECUTABLE(TestPluginTest testplugintest.cpp)
ADD_EXECUTABLE(KodiMysqlDbTest kodimysqldbtest.cpp)

ADD_TEST(NAME TestPluginTest COMMAND TestPluginTest)
ADD_TEST(NAME KodiMysqlDbTest COMMAND KodiMysqlDbTest)


qt5_use_modules(TestPluginTest Test Core)
qt5_use_modules(KodiMysqlDbTest Test Core)





