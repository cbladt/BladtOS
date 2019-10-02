SET (arch_SRC
    Terminal.cpp
    io.asm
    Serialport.cpp
    Boot/Boot.asm
)

SET (arch_HDR
    Terminal.hpp
    io.h
    Serialport.hpp
)

add_library(arch STATIC ${arch_SRC} ${arch_HDR})
target_include_directories(arch PUBLIC .)
