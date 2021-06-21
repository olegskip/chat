cmake_minimum_required(VERSION 3.5)

project(chat_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        windows/start_window.h
        windows/start_window.cpp
        windows/sign_in_window.h
        windows/sign_in_window.cpp
        windows/account_recovery_window.h
        windows/account_recovery_window.cpp
        windows/chat_window.h
        windows/chat_window.cpp
        widgets/message_box.h
        widgets/message_box.cpp
        server/server.h
        server/server.cpp

)

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

target_link_libraries(chat_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(chat_client PRIVATE Qt6::Network)

set_target_properties(chat_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chat_client)
endif()
