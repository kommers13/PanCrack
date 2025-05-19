
cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(PanCrackApp LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)
#find_package(Qt6 REQUIRED COMPONENTS Quick QuickStudioApplication)
find_package(Qt6 6.4.1 REQUIRED COMPONENTS Core Gui Qml Quick)
qt_standard_project_setup()

qt_add_executable(${CMAKE_PROJECT_NAME}
    App/include/signals.h App/signals.cpp
    App/include/commandparser.h App/commandparser.cpp
    App/include/listcommands.h App/listcommands.cpp
    App/include/json.hpp # библиотека для обработки JSON
    App/include/dataconverse.h App/dataconverse.cpp
        App/include/graphdraw.h App/graphdraw.cpp
    # команды
    App/include/commands/clearcommand.h App/commands/clearcommand.cpp
    App/include/commands/prufercommand.h App/commands/prufercommand.cpp
    App/include/commands/createcommand.h App/commands/createcommand.cpp
    App/include/commands/drawcommand.h App/commands/drawcommand.cpp
    App/include/commands/showcommand.h App/commands/showcommand.cpp
    App/include/commands/viewcommand.h App/commands/viewcommand.cpp
    App/include/commands/colorcommand.h App/commands/colorcommand.cpp
    App/include/commands/algorithmcommand.h App/commands/algorithmcommand.cpp
    App/include/commands/checkcommand.h App/commands/checkcommand.cpp
    App/include/commands/helpcommand.h App/commands/helpcommand.cpp

)
qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

# копирование json-файлов в директорию для сборки
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/crtsrc.cmake)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
