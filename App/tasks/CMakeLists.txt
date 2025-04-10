cmake_minimum_required(VERSION 3.21.1)

add_library(taskslib STATIC task7.cpp)

target_include_directories(taskslib PUBLIC include)

