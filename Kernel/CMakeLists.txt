cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)

project ("Kernel" LANGUAGES C CXX ASM_NASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Setup Arch.
add_subdirectory("${_SUBDIR}")

# Setuo Libs.
add_subdirectory("Utility")

set(SRC ${SRC} "main.cpp")

add_executable(${PROJECT_NAME}.elf ${SRC})
target_link_libraries(${PROJECT_NAME}.elf ArchLib)
