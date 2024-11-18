project(Proj_Test)

add_library(${PROJECT_NAME} INTERFACE)

file(GLOB_RECURSE PORJ_SRC_FILE "*/*.c")

target_sources(${PROJECT_NAME} INTERFACE ${PORJ_SRC_FILE})

target_include_directories(${PROJECT_NAME} INTERFACE . freetype)





