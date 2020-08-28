# generated file
cmake_minimum_required( VERSION 2.8 )
include_directories(    ../include
                        ../include/${CMAKE_SYSTEM_NAME} )
add_definitions(-DBUILDNO="TEST")
list(APPEND SOURCES values_print.c values_symbol.c values_code.c values_obj.c values_closure.c values_block.c values_basic.c values_continuation.c values_ivars.c)
add_library(values SHARED ${SOURCES})
