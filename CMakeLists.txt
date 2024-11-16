cmake_minimum_required(VERSION 3.16)
project(Quasiconvex)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*" )

add_executable(
    quasiconvex
    src/main.cpp
    ${SOURCES}
)

add_executable(
    quasiconvex_debug
    src/main.cpp
    ${SOURCES}
)

add_compile_options(quasiconvex, -Ofast -march=native)
