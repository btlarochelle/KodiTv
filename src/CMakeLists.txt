
set(APP_SRCS "")
set(APP_HEADERS "")

add_subdirectory(models)
add_subdirectory(json)

add_executable(${APP_NAME}
  main.cpp
  core.cpp
  ${APP_SRCS}
)

qt5_use_modules(${APP_NAME} Gui Qml Quick)

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_BINARY_DIR}/install/)

