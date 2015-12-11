
set(HEADERS ${HEADERS} PARENT_SCOPE)

foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    #message(STATUS "header dirs tests: "  ${_dir} )
    #message(STATUS "header file tests: "  ${_headerFile} )
    list (APPEND HEADER_DIRS ${_dir})
endforeach()
#message(STATUS "header dirs: "  ${HEADER_DIRS} )

include_directories(
    ${HEADER_DIRS}
    ${PROJECT_SOURCE_DIR}/backends/
)


add_executable(kodiMysqlDbTest kodimysqldbtest.cpp)

target_link_libraries(kodiMysqlDbTest KodiMysqlDb)

add_test(NAME kodiMysqlDbTest COMMAND KodiMysqlDbTest)

qt5_use_modules(kodiMysqlDbTest Test Core)




#target_link_libraries(KodiMysqlDbTest ${PROJECT_BINARY_DIR}/backends/libKodiMysqlDb.so)
#set_target_properties(KodiMysqlDbTest PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
