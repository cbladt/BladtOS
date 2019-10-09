set(Name ArchLib)

# // TODO Somehow hide the internals of this lib (Files not in Public dir) from rest of project.
# // TODO Investigate how to specficy explicit interfaces for each Arch to implement. As of right now they are totally implicit. (Virtuals are slow and do not allow common constructors. CRTP perhaps?)

# Publc
SET (${Name}_PUB_SRC
    Public/Interrupt.cpp
    Public/Terminal.cpp
)

SET (${Name}_PUB_HDR
    Public/Interrupt.hpp
    Public/Serialport.hpp
    Public/Terminal.hpp
)

# Internal
SET (${Name}_SRC    
    Io.asm
    Boot/Boot.asm
)

SET (${Name}_HDR
    Io.h
    Framebuffer.hpp
)

add_subdirectory("libc")

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_PUB_SRC} ${${Name}_HDR} ${${Name}_PUB_HDR})
target_include_directories(${Name} PUBLIC "Public")
target_link_libraries(${Name} UtilityLib etl)
