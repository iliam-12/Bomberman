cmake_minimum_required(VERSION 3.17)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/tools)

project(bomberman)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(raylib_verbose ON)

FIND_PACKAGE(raylib REQUIRED)
INCLUDE_DIRECTORIES(${raylib_SOURCE_DIR}/src)

SET(CMAKE_CXX_FLAGS "-g3 -Wall")

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/*/*.cpp"
    "${PROJECT_SOURCE_DIR}/*/*/*.cpp"
    )

add_executable(bomberman ${all_SRCS})
target_link_libraries(bomberman raylib)

INSTALL(TARGETS bomberman DESTINATION ${CMAKE_SOURCE_DIR})
