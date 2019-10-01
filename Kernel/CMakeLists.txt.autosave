cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE ON)CMAKE_CXX_FLAGS

project ("Kernel" LANGUAGES C CXX ASM_NASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Todo: Move i386 specific stuff to its arch folder.

# Use NASM assembler.
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

# Setup compiler flags
set(FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${FLAGS}")
set(CMAKE_CXX_FLAGS "${FLAGS} -o2")

# Custom link routine..
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtbegin.o" OUTPUT_VARIABLE CRT_BEGIN)
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtend.o" OUTPUT_VARIABLE CRT_END)
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_SOURCE_DIR}/Boot/crti.s -o ${CMAKE_SOURCE_DIR}/Boot/crti.o")
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_SOURCE_DIR}/Boot/crtn.s -o ${CMAKE_SOURCE_DIR}/Boot/crtn.o")
set(CRT_I "${CMAKE_SOURCE_DIR}/Boot/crti.o")
set(CRT_N "${CMAKE_SOURCE_DIR}/Boot/crtn.o")
set(LINK_COMMAND "<CMAKE_LINKER> -T ${CMAKE_SOURCE_DIR}/Boot/Link.ld -melf_i386 <CMAKE_C_LINK_FLAGS> ${CRT_I} ${CRT_BEGIN} <OBJECTS> ${CRT_END} ${CRT_N} -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_C_LINK_EXECUTABLE ${LINK_COMMAND})
set(CMAKE_CXX_LINK_EXECUTABLE ${LINK_COMMAND})
set(SRC "Boot/Boot.asm")

add_subdirectory("Arch")

set(SRC ${SRC} "main.cpp")

add_executable(${PROJECT_NAME}.elf ${SRC})
target_link_libraries(${PROJECT_NAME}.elf arch)
