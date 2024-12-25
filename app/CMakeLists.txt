qt_add_executable(app main.cpp MainWidget.cpp MainWidget.h ${QT_RESOURCES})
include_directories(../src)

target_link_libraries(app
    PUBLIC
    QUVCObject
    PRIVATE
    Qt6::Gui
    Qt6::Widgets
    )

target_include_directories(app PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
