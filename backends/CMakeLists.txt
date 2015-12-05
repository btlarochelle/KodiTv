
#set(INCLUDE PARENT_SCOPE) 
#add_library(TestPlugin ${INCLUDE} testplugin.cpp)

add_library(TestPlugin SHARED testplugin.cpp)
add_library(Test2Plugin SHARED test2plugin.cpp)

qt5_use_modules(TestPlugin Gui Qml Quick)
qt5_use_modules(Test2Plugin Gui Qml Quick)

