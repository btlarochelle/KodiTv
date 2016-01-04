
#set(HEADERS ${HEADERS} PARENT_SCOPE)

#foreach (_headerFile ${HEADERS})
#    get_filename_component(_dir ${_headerFile} PATH)
    #message(STATUS "header dirs tests: "  ${_dir} )
    #message(STATUS "header file tests: "  ${_headerFile} )
#    list (APPEND HEADER_DIRS ${_dir})
#endforeach()
#message(STATUS "header dirs: "  ${HEADER_DIRS} )

#include_directories(
#    ${HEADER_DIRS}
#    ${PROJECT_SOURCE_DIR}/backends/
#)


add_executable(kodiMysqlDbTest kodimysqldbtest.cpp
                               ../src/models/channelmodel.cpp
                               ../src/models/criteria.cpp)
add_executable(channelModelTest channelmodeltest.cpp ../src/models/channelmodel.cpp
                                                     ../src/models/criteria.cpp )
add_executable(channelModelJsonTest channelmodeljsontest.cpp
                                        ../src/json/channelmodelfromjson.cpp
                                        ../src/json/channelmodeltojson.cpp
                                        ../src/models/channelmodel.cpp
                                        ../src/models/criteria.cpp
)
add_executable(criteriaTest criteriatest.cpp ../src/models/criteria.cpp)

target_link_libraries(kodiMysqlDbTest KodiMysqlDb)

#add_test(NAME kodiMysqlDbTest COMMAND kodiMysqlDbTest)

add_test(NAME criteriaTest COMMAND criteriaTest)
add_test(NAME channelModelTest COMMAND channelModelTest)
add_test(NAME channelModelJsonTest COMMAND channelModelJsonTest)

qt5_use_modules(kodiMysqlDbTest Test Core)
qt5_use_modules(channelModelTest Test Core)
qt5_use_modules(channelModelJsonTest Test Core)
qt5_use_modules(criteriaTest Test Core)




