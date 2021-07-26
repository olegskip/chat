cmake_minimum_required(VERSION 3.16.3)

project(chat_server)

find_package(Boost REQUIRED)

add_library(MariaDB_connector SHARED IMPORTED)
set_target_properties(MariaDB_connector PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libmariadbcpp.so)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall -g -pthread")

add_executable(${PROJECT_NAME} 
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/server.h ${CMAKE_SOURCE_DIR}/src/server.cpp 
	${CMAKE_SOURCE_DIR}/src/session.h ${CMAKE_SOURCE_DIR}/src/session.cpp 
	${CMAKE_SOURCE_DIR}/src/packets_manager.h ${CMAKE_SOURCE_DIR}/src/packets_manager.cpp 
	${CMAKE_SOURCE_DIR}/src/packet.h ${CMAKE_SOURCE_DIR}/src/packet.cpp
	${CMAKE_SOURCE_DIR}/src/database_manager.h ${CMAKE_SOURCE_DIR}/src/database_manager.cpp)

target_link_libraries(${PROJECT_NAME} MariaDB_connector)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
