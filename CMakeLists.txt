cmake_minimum_required(VERSION 3.10)
project(3011 C)

set(CMAKE_C_STANDARD 99)
add_executable(3011
        main.c
        libmtm.a
        set.h
        list.h
        uniqueOrderedList/UniqueOrderedList.c
        uniqueOrderedList/uniqueOrderedList.h
        citizen.c
        citizen.h
        mtm_elections.c
        mtm_elections.h
        mtm_print.c
        mtm_print.h
        City.h
        City.c
        typedefs_and_general_functions.c
        typedefs_and_general_functions.h preference.c preference.h Candidate.h Candidate.c)

target_link_libraries(3011 ${CMAKE_SOURCE_DIR}/libmtm.a )
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors ")