cmake_minimum_required(VERSION 3.21.1)


add_library(taskslib STATIC graph.cpp include/graph.h
                            task0.cpp include/task0.h
                            task7.cpp include/task7.h
                            task10.cpp include/task10.h
                            task11.cpp include/task11.h

                        )

target_include_directories(taskslib PUBLIC include)

