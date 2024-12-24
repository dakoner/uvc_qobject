add_executable(simple_app main.cpp ${QT_RESOURCES})
include_directories(../UVCObject)

target_link_libraries(simple_app
    PRIVATE
    UVCObject
    )

target_include_directories(simple_app PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
