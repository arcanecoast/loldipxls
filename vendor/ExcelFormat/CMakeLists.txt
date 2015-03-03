cmake_minimum_required(VERSION 3.1)

project(ExcelFormat)

include_directories(include)

FILE(GLOB EXCELFORMAT_SOURCE_FILES source/*.cpp)
add_library(ExcelFormat STATIC ${EXCELFORMAT_SOURCE_FILES})