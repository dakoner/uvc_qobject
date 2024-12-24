add_executable(main main.cpp ${QT_RESOURCES})
include_directories(../uvc_object)

target_link_libraries(main
    PRIVATE
    ${PROJECT}
    )

target_include_directories(main PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
