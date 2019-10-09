set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Etl Stuff.
set(ETL_PROFILE DEFAULT)
set(_DEFINES "${_DEFINES} -DETL_NO_STL -DETL_NO_NULLPTR_SUPPORT")

set(_SUBDIR "Arch/i386")

# Toolchain stuff. (TODO Nasm is still i386 hardcoded.)
set(TCPRE		    ${TOOLCHAINPREFIX})
set(_LINKER		    "${TCPRE}-gcc")
set(CMAKE_C_COMPILER	    "${TCPRE}-gcc" CACHE INTERNAL "C Compiler" FORCE)
set(CMAKE_CXX_COMPILER	    "${TCPRE}-g++" CACHE INTERNAL "C++ Compiler" FORCE)
set(CMAKE_ASM_NASM_COMPILER "/usr/bin/nasm" CACHE INTERNAL "ASM Compiler" FORCE)
set(CMAKE_AR		    "${TCPRE}-gcc-ar" CACHE INTERNAL "the toolchain archive command" FORCE)
set(CMAKE_OBJCOPY	    "${TCPRE}-objcopy" CACHE INTERNAL "the toolchain objcopy command" FORCE)
set(CMAKE_SIZE_UTIL	    "${TCPRE}-size" CACHE INTERNAL "the toolchain size command" FORCE)
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")

# Use NASM assembler.
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

# Compiler flags.
#set(_WarningsAsError "-Werror")
set(_WarningsAsError "")

set(_FLAGS "-ffreestanding -Wall -Wextra -c ${_WarningsAsError} ${_DEFINES}")
set(_CFLAGS "${_FLAGS} -Wno-strict-aliasing -pedantic")
set(_CXXFLAGS "${_FLAGS} -O2 -flto -fno-exceptions -fno-rtti -Wpedantic -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wlogical-op -Wuseless-cast")
set(CMAKE_C_FLAGS "${_CFLAGS}" CACHE INTERNAL "C compiler options" FORCE)
set(CMAKE_CXX_FLAGS "${_CXXFLAGS}" CACHE INTERNAL "C++ compiler options" FORCE)

# Custom link routine..
set(_BOOTDIR "${CMAKE_SOURCE_DIR}/${_SUBDIR}/Boot")
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtbegin.o" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CRT_BEGIN)
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtend.o" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE CRT_END)
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${_BOOTDIR}/crti.s -o ${_BOOTDIR}/crti.o")
execute_process(COMMAND bash -c "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${_BOOTDIR}/crtn.s -o ${_BOOTDIR}/crtn.o")
set(CRT_I "${_BOOTDIR}/crti.o")
set(CRT_N "${_BOOTDIR}/crtn.o")

set(_CXXLINKOBJS "${CRT_I} ${CRT_BEGIN} <OBJECTS> <LINK_LIBRARIES> ${CRT_END} ${CRT_N}")
set(_CLINKOBJS "OBJECTS> <LINK_LIBRARIES>")

set(CMAKE_C_LINK_EXECUTABLE   "bash -xec \"${_LINKER} -Wl,-T ${CMAKE_SOURCE_DIR}/${_SUBDIR}/Boot/Link.ld -flto -nostdlib ${_CLINKOBJS}   -o <TARGET> -lgcc\"")
set(CMAKE_CXX_LINK_EXECUTABLE "bash -xec \"${_LINKER} -Wl,-T ${CMAKE_SOURCE_DIR}/${_SUBDIR}/Boot/Link.ld -flto -nostdlib ${_CXXLINKOBJS} -o <TARGET> -lgcc\"")

set(_LIBLINKCMD "${CMAKE_AR} rcs <TARGET> <OBJECTS>")
set(CMAKE_C_CREATE_STATIC_LIBRARY ${_LIBLINKCMD})
set(CMAKE_CXX_CREATE_STATIC_LIBRARY ${_LIBLINKCMD})


