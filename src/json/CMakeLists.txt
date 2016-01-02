

set(APP_SRCS ${APP_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/channelmodeltojson.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/channelmodelfromjson.cpp
    PARENT_SCOPE
)

set(APP_HEADERS ${APP_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/channelmodeltojson.h
    ${CMAKE_CURRENT_SOURCE_DIR}/channelmodelfromjson.h
    PARENT_SCOPE
)
