cmake_minimum_required(VERSION 3.26)
project(MyApp LANGUAGES C CXX)

add_subdirectory(tasks)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    "main.cpp"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    taskslib
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
)
