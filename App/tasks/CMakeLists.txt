cmake_minimum_required(VERSION 3.21.1)

add_library(taskslib STATIC graph.cpp
    include/graph.h include/task10.h task10.cpp)

target_include_directories(taskslib PUBLIC include)

