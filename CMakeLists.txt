cmake_minimum_required(VERSION 3.20)
project(raylib_game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find Raylib provided by Nix
find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)

# Link Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
