cmake_minimum_required(VERSION 3.10)
project(lv_mgr C CXX ASM)

set(CMAKE_PROJECT_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_C_FLAGS "-O0")

add_link_options("-Wl,--gc-sections")

include_directories(. include)

add_definitions(-DLV_CONF_INCLUDE_SIMPLE)
add_definitions(-DSDL_VER_RES=480 -DSDL_HOR_RES=480) # 调整长宽
add_definitions(-DSDL_ZOOM=1) # 修改缩放比例

# 不同系统选择不同目录
add_subdirectory(src/platform/windows)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

