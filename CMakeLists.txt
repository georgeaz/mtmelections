cmake_minimum_required(VERSION 3.10)
project(nos5a C)

set(CMAKE_C_STANDARD 99)
add_executable(nos5a
        mtm_elections_tests.h
        mtm_elections_tests.c
        uniqueOrderedListTest.c
        uniqueOrderedListTest.h
        libmtm.a
        set.h
        list.h
        mtm_uol/UniqueOrderedList.c
        mtm_uol/uniqueOrderedList.h
        citizen.c
        citizen.h
        mtm_elections.c
        mtm_elections.h
        mtm_print.c
        mtm_print.h
        City.h
        City.c
        exampleMain.c
        typedefs_and_general_functions.c
        typedefs_and_general_functions.h preference.c preference.h Candidate.h Candidate.c Vote.c Vote.h mayor.h mayor.c)

target_link_libraries(nos5a ${CMAKE_SOURCE_DIR}/libmtm.a )
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors ")