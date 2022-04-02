cmake_minimum_required(VERSION 3.21)
project(ExperimentAMS)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(ExperimentAMS main.cpp menu.cpp menu.h service.cpp service.h class.cpp class.h tool.cpp tool.h card_service.cpp card_service.h bill_service.cpp bill_service.h card_file.cpp card_file.h global_var.cpp global_var.h bill_file.cpp bill_file.h linklist.cpp linklist.h)
