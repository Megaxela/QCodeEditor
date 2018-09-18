cmake_minimum_required(VERSION 3.12)
project(QCodeEditor)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        src/internal/QCodeEditor.cpp
        include/internal/QCodeEditor.hpp
        src/internal/QLineNumberArea.cpp
        include/internal/QLineNumberArea.hpp
        src/internal/QCXXHighlighter.cpp
        include/internal/QCXXHighlighter.hpp
)

set(CMAKE_AUTOMOC On)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core    CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui     CONFIG REQUIRED)

qt5_add_resources(RESOURCE_ADDED ${QT_RESOURCES})

add_executable(QCodeEditor
    ${MAIN_FILE}
    ${SOURCE_FILES}
    ${INCLUDE_FILES}
    ${RESOURCE_ADDED}
)

target_include_directories(QCodeEditor PUBLIC
    include
)

target_compile_options(QCodeEditor
    PRIVATE
    -ansi
    -pedantic
    -Wall
    -Wextra
    -Weffc++
    -Woverloaded-virtual
    -Winit-self
    -Wunreachable-code
)

target_link_libraries(QCodeEditor
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)