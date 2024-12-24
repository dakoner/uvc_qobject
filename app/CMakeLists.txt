qt_add_executable(app main.cpp MainWidget.cpp MainWidget.h ${QT_RESOURCES})
include_directories(../UVCQObject)

target_link_libraries(app
    PUBLIC
    UVCQObject
    PRIVATE
    Qt6::Gui
    Qt6::Widgets
    )

target_include_directories(app PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
