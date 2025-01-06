project(${CMAKE_PROJECT_NAME})

set(EXCLUDE_DIR "") # 排除的目录
file(GLOB_RECURSE PROJ_FILE "*.c")

if (EXCLUDE_DIR)
    list(FILTER PROJ_FILE EXCLUDE REGEX "^${CMAKE_CURRENT_SOURCE_DIR}/${EXCLUDE_DIR}/")
endif ()

add_executable(${PROJECT_NAME})

target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
)

target_link_options(
        ${PROJECT_NAME}
        PRIVATE
        "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        "-Wl,-Map=${CMAKE_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}.map"
        "-Wl,--no-gc-sections"
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ProjSrc
        ProjLib
        ProjTest
        ${CMAKE_SOURCE_DIR}/bin/SDL2.dll
        ${CMAKE_SOURCE_DIR}/bin/libjson-c.dll
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        ${PROJ_FILE}
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
)

if (CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif ()