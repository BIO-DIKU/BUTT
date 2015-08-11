
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/Search 
	${CMAKE_CURRENT_SOURCE_DIR}/Tests )

FILE(GLOB_RECURSE SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_library(BUTT-lib ${SRCFILES})

set_target_properties( BUTT-lib PROPERTIES PREFIX "" )

add_executable( BUTTex main.cpp )
target_link_libraries( BUTTex BUTT-lib )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR} )
