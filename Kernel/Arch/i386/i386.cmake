set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(_SUBDIR "Arch/i386")

# Toolchain stuff.
set(_GCC "/usr/bin/gcc")
set(CMAKE_C_COMPILER	    ${_GCC} CACHE INTERNAL "C Compiler" FORCE)
set(CMAKE_CXX_COMPILER	    ${_GCC} CACHE INTERNAL "C++ Compiler" FORCE)
set(CMAKE_ASM_NASM_COMPILER /usr/bin/nasm CACHE INTERNAL "ASM Compiler" FORCE)
set(CMAKE_AR		    /usr/bin/gcc-ar CACHE INTERNAL "the toolchain archive command" FORCE)
set(CMAKE_OBJCOPY	    /usr/bin/objcopy CACHE INTERNAL "the toolchain objcopy command" FORCE)
set(CMAKE_SIZE_UTIL	    /usr/bin/size CACHE INTERNAL "the toolchain size command" FORCE)
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")

# Use NASM assembler.
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

# Compiler flags.
#set(_WarningAsError "-Werror")
set(_WarningAsError "")
set(_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs ${_WarningAsError}")
set(_CFLAGS "${_FLAGS} -Wall -Wextra -Wno-strict-aliasing -pedantic")
set(_CXXFLAGS "${_FLAGS} -O2 -Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wlogical-op -Wuseless-cast")
set(CMAKE_C_FLAGS "${_CFLAGS}" CACHE INTERNAL "C compiler options" FORCE)
set(CMAKE_CXX_FLAGS "${_CXXFLAGS}" CACHE INTERNAL "C++ compiler options" FORCE)

# Custom link routine..
#execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtbegin.o" OUTPUT_VARIABLE CRT_BEGIN)
#execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtend.o" OUTPUT_VARIABLE CRT_END)
#execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_SOURCE_DIR}/Boot/crti.s -o ${CMAKE_SOURCE_DIR}/Boot/crti.o")
#execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_SOURCE_DIR}/Boot/crtn.s -o ${CMAKE_SOURCE_DIR}/Boot/crtn.o")
#set(CRT_I "${CMAKE_SOURCE_DIR}/Boot/crti.o")
#set(CRT_N "${CMAKE_SOURCE_DIR}/Boot/crtn.o")
set(_LINKCMD "<CMAKE_LINKER> -T ${CMAKE_SOURCE_DIR}/${_SUBDIR}/Boot/Link.ld -melf_i386 <CMAKE_C_LINK_FLAGS> ${CRT_I} ${CRT_BEGIN} <OBJECTS> ${CRT_END} ${CRT_N} -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_C_LINK_EXECUTABLE ${_LINKCMD})
set(CMAKE_CXX_LINK_EXECUTABLE ${_LINKCMD})

