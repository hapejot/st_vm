# generated file
cmake_minimum_required( VERSION 2.8 )
include_directories(    ../include
                        ../include/${CMAKE_SYSTEM_NAME} )
find_package( dl )
add_definitions(-DBUILDNO="TEST")
list(APPEND SOURCES prim_obj_identical.c prim_print.c prim_sym_compare.c)
add_library(primitives SHARED ${SOURCES})
add_executable( prim_tst main.c )
target_link_libraries( prim_tst PUBLIC primitives values dl )
install( TARGETS prim_tst RUNTIME DESTINATION bin )
