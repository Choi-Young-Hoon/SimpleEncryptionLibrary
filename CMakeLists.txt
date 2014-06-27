cmake_minimum_required(VERSION 2.6)


#Project configuration

project(AEL)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})


#include files

include_directories(include)


#Library configuration

file(

        GLOB_RECURSE

        source_files

        src/*

        include/*

)

add_library(

        ael

        SHARED

        ${source_files}

)