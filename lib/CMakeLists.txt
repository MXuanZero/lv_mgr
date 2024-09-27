project(Proj_Lib)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE PORJ_Lib_FILE "lv_drivers/*.c" "lvgl/demos/*.c" "lvgl/src/*.c" "lvgl/examples/*.c")

target_sources(${PROJECT_NAME} INTERFACE ${PORJ_Lib_FILE})

target_include_directories(${PROJECT_NAME} INTERFACE .)





