set(Name ArchLib)

# // TODO Investigate how to specficy explicit interfaces for each Arch to implement. As of right now they are totally implicit. (Virtuals are slow and do not allow common constructors. CRTP perhaps?)

# Publc
SET (${Name}_PUB_SRC
    Public/Interrupt.cpp
    Public/Terminal.cpp
    Public/Log.cpp
)

SET (${Name}_PUB_HDR
    Public/Interrupt.hpp
    Public/Serialport.hpp
    Public/Terminal.hpp
    Public/Log.hpp
)

# Internal
SET (${Name}_SRC    
    Internal/Io.asm
    Boot/Boot.asm    
)

SET (${Name}_HDR
    Internal/Io.h
    Internal/Framebuffer.hpp
    Internal/Serialport.hpp   
)

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_PUB_SRC} ${${Name}_HDR} ${${Name}_PUB_HDR})
target_include_directories(${Name} PUBLIC "Public")
target_link_libraries(${Name} UtilityLib etl)
