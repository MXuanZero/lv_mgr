project(ProjLib)

include(${CMAKE_SOURCE_DIR}/cmake/freetype.cmake)

set(EXCLUDE_DIR "") # 排除的目录
file(GLOB_RECURSE
    PORJ_LIB_FILE
    "lvgl/src/*.c"
    "lv_drivers/sdl/*.c"
)

if(EXCLUDE_DIR)
    list(FILTER PORJ_LIB_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif()

add_library(${PROJECT_NAME} STATIC)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE
    PRIVATE
    ProjSrc
    PUBLIC
    freetype
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${PORJ_LIB_FILE}
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
)

if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()