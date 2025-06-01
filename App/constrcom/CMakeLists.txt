cmake_minimum_required(VERSION 3.16)

project(ConstrCom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS " -static")

add_executable(ConstrCom
    include/json.hpp
    main.cpp)

target_link_libraries(ConstrCom -static-libgcc -static-libstdc++)
