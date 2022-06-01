cmake_minimum_required(VERSION 3.2)

set(DIR_NAME "${DIR_NAME}_Tricks_")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS -fdeclspec)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    add_executable(${DIR_NAME}SetGetPointer set_get_pointOperation.cpp)
else()
    message("Clang is required for this!")
endif()
