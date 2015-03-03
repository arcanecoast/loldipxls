cmake_minimum_required(VERSION 3.1)

project(lollibs)

include_directories(include)

FILE(GLOB LOLLIBS_SOURCE_FILES src/*.cpp)
add_library(lollibs STATIC ${LOLLIBS_SOURCE_FILES})