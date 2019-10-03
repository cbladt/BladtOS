SET (Utility_SRC
	Types.cpp
)

SET (Utility_HDR
	Types.hpp
	Vga.hpp
)

add_library(UtilityLib STATIC ${Utility_SRC} ${Utility_HDR})
target_include_directories(UtilityLib PUBLIC .)
