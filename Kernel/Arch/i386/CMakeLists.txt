set(Name ArchLib)

# // TODO Investigate how to specficy explicit interfaces for each Arch to implement. As of right now they are totally implicit. (Virtuals are slow and do not allow common constructors. CRTP perhaps?)

# Public
set(${Name}_PUB_SRC
    Public/Interrupt.cpp
    Public/Terminal.cpp
    Public/LoadGDT.asm
)

set(${Name}_PUB_HDR
    Public/Interrupt.hpp
    Public/Serialport.hpp
    Public/Terminal.hpp
    Public/Log.hpp
    Public/LoadGDT.hpp
)

# Internal
set(${Name}_SRC
    Internal/Io.asm
    Boot/Boot.asm    
)

set(${Name}_HDR
    Internal/Io.hpp
    Internal/Framebuffer.hpp
    Internal/Serialport.hpp   
)

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_PUB_SRC} ${${Name}_HDR} ${${Name}_PUB_HDR})
target_include_directories(${Name} PUBLIC "Public")
target_link_libraries(${Name} UtilityLib etl)
