cmake_minimum_required(VERSION 2.6)


#Project configuration

project(SEL)

option(BUILD_TEST_PROGRAM "Build the example" TRUE)

option(CMAKE_BUILD_TYPE "Build Type : Release or Debug")

set(LIBRARY_OUTPUT_PATH ../build-sel/lib/${CMAKE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH ../build-sel/bin/${CMAKE_BUILD_TYPE})

option(BUILD_SHARED_LIBS "TRUE to build AEL as shared library, FALSE to build it as static library" TRUE)


#include files

include_directories(include)


#Library configuration

file(

        GLOB_RECURSE

        source_files

        src/SEL.cpp

		src/AES.cpp

		src/LargeInt.cpp

		src/MD5.cpp

		src/CRC.cpp

		include/SEL.hpp

)

add_library(

        sel

        ${source_files}

)

add_executable(
		seltools

		src/main.cpp

		include/SEL.hpp
)

target_link_libraries(seltools sel)

if(${BUILD_TEST_PROGRAM} MATCHES "ON")

add_executable(
		seltest

		src/Test.cpp

		include/SEL.hpp
)

target_link_libraries(seltest sel)

endif(${BUILD_TEST_PROGRAM} MATCHES "ON")
