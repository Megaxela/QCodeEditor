cmake_minimum_required(VERSION 3.6)
project(QCodeEditor)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_EXAMPLE "Example building required" Off)

if (${BUILD_EXAMPLE})
    message(STATUS "QCodeEditor example will be built.")
    add_subdirectory(example)
endif()

set(RESOURCES_FILE
    resources/resources.qrc
)

set(INCLUDE_FILES
    include/QHighlightRule
    include/QCodeEditor
    include/QCXXHighlighter
    include/QLineNumberArea
    include/QStyleSyntaxHighlighter
    include/QSyntaxStyle
    include/QGLSLCompleter
    include/QGLSLHighlighter
    include/QLanguage
    include/QXMLHighlighter
    include/QJSONHighlighter
    include/internal/QHighlightRule.hpp
    include/internal/QCodeEditor.hpp
    include/internal/QCXXHighlighter.hpp
    include/internal/QLineNumberArea.hpp
    include/internal/QStyleSyntaxHighlighter.hpp
    include/internal/QSyntaxStyle.hpp
    include/internal/QGLSLCompleter.hpp
    include/internal/QGLSLHighlighter.hpp
    include/internal/QLanguage.hpp
    include/internal/QXMLHighlighter.hpp
    include/internal/QJSONHighlighter.hpp
)

set(SOURCE_FILES
    src/internal/QCodeEditor.cpp
    src/internal/QLineNumberArea.cpp
    src/internal/QCXXHighlighter.cpp
    src/internal/QSyntaxStyle.cpp
    src/internal/QStyleSyntaxHighlighter.cpp
    src/internal/QGLSLCompleter.cpp
    src/internal/QGLSLHighlighter.cpp
    src/internal/QLanguage.cpp
    src/internal/QXMLHighlighter.cpp
    src/internal/QJSONHighlighter.cpp
)

# Create code for QObjects
set(CMAKE_AUTOMOC On)

# Create code from resource files
set(CMAKE_AUTORCC ON)

# Find includes in corresponding build directories
find_package(Qt5Core    CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui     CONFIG REQUIRED)

add_library(QCodeEditor STATIC
    ${RESOURCES_FILE}
    ${SOURCE_FILES}
    ${INCLUDE_FILES}
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