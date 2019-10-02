SET (arch_SRC
    Framebuffer.cpp
    io.asm
    Serialport.cpp
    Boot/Boot.asm
)

SET (arch_HDR
    Types.hpp
    Framebuffer.hpp
    io.h
    Serialport.hpp
)

add_library(arch STATIC ${arch_SRC} ${arch_HDR})
target_include_directories(arch PUBLIC .)
