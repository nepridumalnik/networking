cmake_minimum_required(VERSION 3.25)
project(networking)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
)

include(conan)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(src)
