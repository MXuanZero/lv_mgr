project(ProjTest)

set(EXCLUDE_DIR "") # 排除的目录
file(GLOB_RECURSE PROJ_SRC_FILE "*.c")

if (EXCLUDE_DIR)
    list(FILTER PROJ_SRC_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif ()

add_library(${PROJECT_NAME} STATIC)

target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ProjLib
        ProjSrc
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        ${PROJ_SRC_FILE}
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
)

if (CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif ()