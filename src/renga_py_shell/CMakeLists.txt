cmake_minimum_required(VERSION 3.5)

project(renga_py_shell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED RENGA_SDK_PATH)
    message(SEND_ERROR "Renga SDK not found, add -DRENGA_SDK_PATH=<Renga SDK path>")
else()
    message("-- Found Renga SDK: ${RENGA_SDK_PATH}")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
)
find_package (Python REQUIRED COMPONENTS Interpreter Development)

if (NOT DEFINED Python_EXECUTABLE)
    message(SEND_ERROR "Python not found")
endif()

if (NOT ${Python_INTERPRETER_ID} MATCHES "Python")
    message(SEND_ERROR "Only CPython interpreter supported")
endif()

set(PROJECT_SOURCES
    main.cpp
    stdafx.cpp
    RengaPyShellPlugin.cpp
    RengaEventsHandler.cpp
    PluginToolButtons.cpp
    RengaPyShellButtonHandler.cpp
    ShellWidget.cpp
    PythonCodeEditor.cpp
    python_code_handler.cpp
    qt_resources_data.qrc
    ShellWidget.ui
)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#set(PROJECT_RESOURCES
#    renga_py_shell.rndesc
#    icons/py_logo.png
#    icons/repa_logo.png
#    icons/ui_form_run_script.png
#)

#foreach (RESOURCE_FILE ${PROJECT_RESOURCES})
#    configure_file("${RESOURCE_FILE}" "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${RESOURCE_FILE}")
#endforeach()

if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
    configure_file(renga_py_shell.rndesc ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/renga_py_shell.rndesc COPYONLY)
    configure_file(icons/py_logo.png ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/icons/py_logo.png COPYONLY)
    configure_file(icons/repa_logo.png ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/icons/repa_logo.png COPYONLY)
    configure_file(icons/ui_form_run_script.png ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/icons/ui_form_run_script.png COPYONLY)
else()
    configure_file(renga_py_shell.rndesc renga_py_shell.rndesc COPYONLY)
    configure_file(icons/py_logo.png icons/py_logo.png COPYONLY)
    configure_file(icons/repa_logo.png icons/repa_logo.png COPYONLY)
    configure_file(icons/ui_form_run_script.png icons/ui_form_run_script.png COPYONLY)
endif()

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
#    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Python::Module
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${RENGA_SDK_PATH}/C++/Include
    ${RENGA_SDK_PATH}/tlb
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION_MAJOR}${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
