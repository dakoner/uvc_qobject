add_executable(main main.cpp ${QT_RESOURCES})
include_directories(../UVCObject)

target_link_libraries(main
    PRIVATE
    UVCObject
    )

target_include_directories(main PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
