
#set(HEADERS ${HEADERS}
#    ${CMAKE_CURRENT_SOURCE_DIR}/kodimysqldatabase.h
#    PARENT_SCOPE
#)


#add_library(TestPlugin SHARED ${INCLUDE} testplugin.cpp)
#add_library(Test2Plugin SHARED ${INCLUDE} test2plugin.cpp)
#add_library(KodiMysqlDb SHARED ${HEADERS} kodimysqldatabase.cpp)
add_library(KodiMysqlDb SHARED kodimysqldatabase.cpp querythread.cpp
                               ../src/models/channelmodel.cpp
                               ../src/models/criteria.cpp
)

#qt5_use_modules(TestPlugin Gui Qml Quick)
#qt5_use_modules(Test2Plugin Gui Qml Quick)
qt5_use_modules(KodiMysqlDb Core Sql)

#install(TARGETS TestPlugin DESTINATION ${CMAKE_BINARY_DIR}/install/plugins/)
#install(TARGETS Test2Plugin DESTINATION ${CMAKE_BINARY_DIR}/install/plugins/)
install(TARGETS KodiMysqlDb DESTINATION ${CMAKE_BINARY_DIR}/install/plugins/)

