cmake_minimum_required(VERSION 3.16.3)

project(chat_server)

find_package(Boost REQUIRED)
# find_package(MYSQLCPPCONN REQUIRED)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall -g -pthread -lmysqlcppconn")

add_executable(${PROJECT_NAME} 
	main.cpp 
	server.h server.cpp 
	session.h session.cpp 
	packets_manager.h packets_manager.cpp 
	packet.h packet.cpp
	database_manager.h database_manager.cpp)

# include_directories(/usr/include/cppconn)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
