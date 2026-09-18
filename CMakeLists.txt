cmake_minimum_required(VERSION 3.20)
project(harmonia_ecs C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type" FORCE)
endif()

# -U_FORTIFY_SOURCE silences glibc warnings when building with -O0
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -U_FORTIFY_SOURCE -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# 1. Gather all C source files in src/
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "src/*.c")

# 2. Build your project as a static library (or SHARED if preferred)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

# Exclude include paths for users/tests linking against your library
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Subdirectories
add_subdirectory(tests)
