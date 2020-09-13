cmake_minimum_required(VERSION 3.7)
project(proy)


add_executable(${PROJECT_NAME} proyecciones.c)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(proy m /lib/libSDL2.so)
set(EXECUTABLE_OUTPUT_PATH ..)
