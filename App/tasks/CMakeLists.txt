cmake_minimum_required(VERSION 3.21.1)

<<<<<<< HEAD
add_library(taskslib STATIC graph.cpp
    include/graph.h include/task10.h task10.cpp)
=======
add_library(taskslib STATIC graph.cpp include/graph.h
                            task7.cpp include/task7.h)
>>>>>>> 4f8a85d4ccd7eddb4cf9a57fc93cb12aaac9d561

target_include_directories(taskslib PUBLIC include)

