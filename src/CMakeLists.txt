
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/backendplugininterface.h PARENT_SCOPE )

add_executable(KodiTv
  main.cpp
  koditv.cpp
)

qt5_use_modules(KodiTv Gui Qml Quick)

install(TARGETS KodiTv DESTINATION ${CMAKE_BINARY_DIR}/install/)

