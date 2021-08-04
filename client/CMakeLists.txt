cmake_minimum_required(VERSION 3.5)

project(chat_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
include_directories(${PROJECT_NAME} PUBLIC ${PARENT_DIR}/common_headers)

add_compile_definitions(IS_QT)

set(PROJECT_SOURCES
    main.cpp
    windows/start_window.h windows/start_window.cpp
    windows/log_in_window.h windows/log_in_window.cpp
    windows/chat_window.h windows/chat_window.cpp
    windows/sign_up_window.h windows/sign_up_window.cpp
    widgets/informative_dialog.h widgets/informative_dialog.cpp
    widgets/messages_box.h widgets/messages_box.cpp
    widgets/message_widget.h widgets/message_widget.cpp
    server_connection/server_connection.h server_connection/server_connection.cpp
    ${PARENT_DIR}/common_headers/responses_codes.h ${PARENT_DIR}/common_headers/requests_types.h
    ${PARENT_DIR}/common_headers/message.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chat_client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(chat_client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(chat_client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(chat_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(chat_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chat_client)
endif()
