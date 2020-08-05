# generated file
cmake_minimum_required( VERSION 2.8 )
include_directories(    ../include
                        ../include/${CMAKE_SYSTEM_NAME} )
add_definitions(-DBUILDNO="TEST")
list(APPEND SOURCES oint.c o_read_lines.c o_read_words.c)
add_library(osrc SHARED ${SOURCES})
add_executable( tst main.c )
target_link_libraries( tst PUBLIC osrc values )
install( TARGETS tst RUNTIME DESTINATION bin )
