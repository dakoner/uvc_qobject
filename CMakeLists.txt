cmake_minimum_required(VERSION 3.28)

set(PROJECT "uvc_qobject")

project(${PROJECT} LANGUAGES CXX)
# 3rd party tools
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(${Qt6Widgets_INCLUDE_DIRS})
add_definitions(${Qt6Widgets_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")

if(NOT DEFINED HEADERS)
    file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
endif()

if(NOT DEFINED SOURCES)
    file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
endif()

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})


qt_add_library(${PROJECT} STATIC uvc_qobject.cpp uvc_qobject.h ${QT_RESOURCES})

target_link_libraries(${PROJECT}
    PUBLIC
    Qt6::Core
    usb
    uvc
    jpeg
    )

add_subdirectory(app)

