SET (arch_SRC
    Framebuffer.cpp
    io.asm
)

SET (arch_HDR
    Framebuffer.hpp
    io.h
)

add_library(arch STATIC ${arch_SRC} ${arch_HDR})
target_include_directories(arch PUBLIC .)
