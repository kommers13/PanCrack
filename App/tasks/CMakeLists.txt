cmake_minimum_required(VERSION 3.21.1)


add_library(taskslib STATIC graph.cpp include/graph.h
                            task0.cpp include/task0.h
                            task7.cpp include/task7.h
                            task10.cpp include/task10.h
                            task11.cpp include/task11.h
                            task1.cpp include/task1.h
                            task2.cpp include/task2.h
                            task4.cpp include/task4.h
                            task5.cpp include/task5.h
                            task6.cpp include/task6.h
                            task8.cpp include/task8.h
                            task3.cpp include/task3.h
                            task9.cpp include/task9.h
                            task12.cpp include/task12.h
                            hamilton.cpp include/hamilton.h
                        )

target_include_directories(taskslib PUBLIC include)

