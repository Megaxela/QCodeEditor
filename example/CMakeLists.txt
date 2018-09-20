cmake_minimum_required(VERSION 3.6)
project(QCodeEditorExample)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC On)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core    CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui     CONFIG REQUIRED)

add_executable(QCodeEditorExample
    resources/demo_resources.qrc
    src/main.cpp
    src/MainWindow.cpp
    include/MainWindow.hpp
)

target_include_directories(QCodeEditorExample PUBLIC
    include
)

target_link_libraries(QCodeEditorExample
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    QCodeEditor
)