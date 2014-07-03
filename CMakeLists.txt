cmake_minimum_required(VERSION 2.6)


#Project configuration

project(AEL)

option(BUILD_TEST_PROGRAM "Build the example" TRUE)

option(CMAKE_BUILD_TYPE "Build Type : Release or Debug")

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED_LIBS "TRUE to build AEL as shared librarie, FALSE to build it as static librarie" TRUE)


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
		
		src/MD5.cpp
		
		include/AEL.hpp

)

add_library(

        ael

        ${source_files}

)

if(${BUILD_TEST_PROGRAM} MATCHES "ON")

add_executable(
		ael-test
		
		src/Test.cpp
		
		include/ael.hpp
)

target_link_libraries(ael-test ael)

endif(${BUILD_TEST_PROGRAM} MATCHES "ON")