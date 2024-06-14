message(STATUS "Initialazing conan")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/generators)

find_package(GTest REQUIRED)
