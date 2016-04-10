cmake_minimum_required(VERSION 3.0)

project(livogis)

set(SRCS
	  main.c
	  )

set(HEADERS
	 )

find_package(LibXml2 REQUIRED)

message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})

set(CMAKE_C_FLAGS "-std=c99")

include_directories(${LIBXML2_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
add_executable(livogis ${SRCS} ${HEADERS})
target_link_libraries(livogis ${LIBXML2_LIBRARIES})
