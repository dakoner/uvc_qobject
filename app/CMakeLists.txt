qt_add_executable(main main.cpp MainWidget.cpp MainWidget.h ${QT_RESOURCES})
include_directories(../src)

target_link_libraries(main
    PRIVATE
    ${PROJECT}
    Qt6::Gui
    Qt6::Widgets
    )

target_include_directories(main PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
