cmake_minimum_required(VERSION 3.10)
project(lv_mgr C CXX ASM)

set(CMAKE_PROJECT_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-O3")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker.ld")

include_directories(include)

add_definitions(-DLV_CONF_INCLUDE_SIMPLE)
add_definitions(-DSDL_VER_RES=480 -DSDL_HOR_RES=480) # 调整长宽
add_definitions(-DSDL_ZOOM=1) # 修改缩放比例

add_executable(${PROJECT_NAME})

add_subdirectory(lib)
add_subdirectory(src)

target_link_libraries(
        ${PROJECT_NAME}
        Proj_Src
        Proj_Lib
        ${CMAKE_SOURCE_DIR}/bin/SDL2.dll
        ${CMAKE_SOURCE_DIR}/bin/libjson-c.dll
)
