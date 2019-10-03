set(Name ArchLib)

SET (${Name}_SRC
    Terminal.cpp
    io.asm    
    Boot/Boot.asm
)

SET (${Name}_HDR
    Terminal.hpp
    io.h
    Serialport.hpp
    Serialport.inc
    Framebuffer.hpp
)
add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_HDR})
target_include_directories(${Name} PUBLIC .)
target_link_libraries(${Name} UtilityLib)

