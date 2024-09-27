project(Proj_Src)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE PORJ_SRC_FILE "gui/*.c" "port/*.c")

target_sources(${PROJECT_NAME} INTERFACE ${PORJ_SRC_FILE})

target_include_directories(${PROJECT_NAME} INTERFACE . gui gui/page gui/img gui/mgr port)





