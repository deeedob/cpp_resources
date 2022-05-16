cmake_minimum_required(VERSION 3.2)
project(cpp_resources)

set(BUILD_EXAMPLES ON CACHE BOOL "build examples")

if(BUILD_EXAMPLES)
 add_subdirectory(examples)
endif()