project(Proj_Lib)

add_subdirectory(freetype)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE PORJ_Lib_FILE "lv_drivers/sdl/*.c" "lvgl/src/*.c")

target_sources(${PROJECT_NAME} INTERFACE ${PORJ_Lib_FILE})

target_include_directories(${PROJECT_NAME} INTERFACE . freetype/include)

target_link_libraries(${PROJECT_NAME} INTERFACE freetype)