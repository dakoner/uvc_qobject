cmake_minimum_required(VERSION 3.28)

set(PROJECT "uvc_qobject")

project(${PROJECT} LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(${Qt6Widgets_INCLUDE_DIRS})
add_definitions(${Qt6Widgets_DEFINITIONS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Widgets_EXECUTABLE_COMPILE_FLAGS} -Wall -Werror  -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")

add_subdirectory(UVCObject)
add_subdirectory(simple_app)
add_subdirectory(UVCQObject)
#add_subdirectory(src)
#add_subdirectory(app)