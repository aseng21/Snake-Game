cmake_minimum_required(VERSION 3.28)
project($ENV{PROJECT_NAME} C)

set(CMAKE_C_STANDARD $ENV{C_STANDARD})
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

set(SDL2_Path $ENV{SDL2_PATH})
set(SDL2_TTF_Path $ENV{SDL2_TTF_PATH})

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}, ${SDL2_TTF_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.c
        FilePaths.h
        game.c
        render.c
        menu.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})