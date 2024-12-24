if(NOT DEFINED HEADERS)
    file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
endif()

if(NOT DEFINED SOURCES)
    file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
endif()

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

qt_add_library(UVCQObject STATIC ${HEADERS} ${SOURCES} ${QT_RESOURCES})

target_link_libraries(UVCQObject
    PUBLIC
    Qt6::Core
    usb
    uvc
    jpeg
    )
