
set(HEADERS ${HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/backendplugininterface.h PARENT_SCOPE )

add_executable(${APP_NAME}
  main.cpp
  core.cpp
)

qt5_use_modules(${APP_NAME} Gui Qml Quick)

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_BINARY_DIR}/install/)

