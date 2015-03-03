cmake_minimum_required(VERSION 3.1)

add_subdirectory(vendor/ExcelFormat)
add_subdirectory(vendor/lollibs)

project(loldipxls)

include_directories(. vendor/ExcelFormat/include vendor/lollibs/include)

FILE(GLOB LOLLIBS_SOURCE_FILES *.cpp)
add_executable(loldipxls ${LOLLIBS_SOURCE_FILES})
target_link_libraries(loldipxls ExcelFormat lollibs)