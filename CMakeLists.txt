cmake_minimum_required(VERSION 2.6)


#Project configuration

project(AEL)

option(CMAKE_BUILD_TYPE "Build Type : Release or Debug")

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED_LIBS "TRUE to build AEL as shared libraries, FALSE to build it as static libraries" TRUE)

#include files

include_directories(include)


#Library configuration

file(

        GLOB_RECURSE

        source_files

        src/AEL.cpp
		
		src/AES.hpp
		
		src/Algo.cpp
		
		src/LargeInt.cpp
		
		include/AEL.hpp

)

add_library(

        ael-${CMAKE_BUILD_TYPE}

        ${source_files}

)