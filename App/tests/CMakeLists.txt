cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_AUTOMOC ON)

project(Tests)

find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

# это означает, что проект в папке ../tasks относительно текущей будет создан и помещен в папку сборки ${CMAKE_BINARY_DIR}/tasks
add_subdirectory(../tasks ${CMAKE_BINARY_DIR}/tasks)    # CMAKE_BINARY_DIR - это путь сборки для проекта Tests

message(STATUS "Binary directory of project \"Tests\": ${CMAKE_BINARY_DIR}")

qt_add_executable(Tests
    main_test.cpp
    include/testgraph.h testgraph.cpp
    include/testtask10.h testtask10.cpp
    include/testtask7.h testtask7.cpp
    include/testtask11.h testtask11.cpp
    include/testtask1.h testtask1.cpp
    include/testtask2.h testtask2.cpp
    include/testtask5.h testtask5.cpp





)

target_link_libraries(Tests PRIVATE taskslib Qt6::Test Qt6::Widgets)



