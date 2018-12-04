cmake_minimum_required(VERSION 3.12)
project(homework1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(homework1
        main.c
        UniqueOrderedList.c
        uniqueOrderedList.h)
