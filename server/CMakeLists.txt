cmake_minimum_required(VERSION 3.1.0)

project(chat_server)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_library(MariaDB_connector SHARED IMPORTED)
set_target_properties(MariaDB_connector PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libmariadbcpp.so)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options(-Wall -Wextra -g)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
include_directories(${PROJECT_NAME} PUBLIC ${PARENT_DIR}/common_headers)

add_executable(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/server.h ${CMAKE_SOURCE_DIR}/src/server.cpp 
	${CMAKE_SOURCE_DIR}/src/session.h ${CMAKE_SOURCE_DIR}/src/session.cpp 
	${CMAKE_SOURCE_DIR}/src/packets_manager.h ${CMAKE_SOURCE_DIR}/src/packets_manager.cpp 
	${CMAKE_SOURCE_DIR}/src/packet.h ${CMAKE_SOURCE_DIR}/src/packet.cpp
	${CMAKE_SOURCE_DIR}/src/database_manager.h ${CMAKE_SOURCE_DIR}/src/database_manager.cpp
	${PARENT_DIR}/common_headers/responses_codes.h ${PARENT_DIR}/common_headers/requests_types.h
	${PARENT_DIR}/common_headers/message.h)


target_link_libraries(${PROJECT_NAME} MariaDB_connector)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
