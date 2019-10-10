cmake_minimum_required(VERSION 3.12)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(Name "Kernel.elf")

project (${Name} LANGUAGES C CXX ASM_NASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Setup Arch.
add_subdirectory("${_SUBDIR}")

# Setup Libs.
add_subdirectory("Utility")
add_subdirectory("BLibC")
add_subdirectory("etl")

set(D "KernelSource")
set(${Name}_SRC
	${D}/KernelMain.cpp
	${D}/Kernel.cpp
)

set(${Name}_HDR
	${D}/Kernel.hpp
)

add_executable(${Name} ${${Name}_SRC} ${${Name}_HDR})
target_include_directories(${Name} PRIVATE ${D})
target_link_libraries(etl INTERFACE BLibC)
target_link_libraries(${PROJECT_NAME} ArchLib etl BLibC)

