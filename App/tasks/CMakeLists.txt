cmake_minimum_required(VERSION 3.21.1)

add_library(taskslib STATIC graph.cpp include/graph.h
                            task7.cpp include/task7.h)

target_include_directories(taskslib PUBLIC include)

