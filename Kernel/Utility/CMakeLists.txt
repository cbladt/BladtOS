set(Name UtilityLib)

set(${Name}_SRC
	Types.cpp
)

set(${Name}_HDR
	Types.hpp
	Vga.hpp		
	Log/DummyLogger.hpp
	Log/Logger.hpp
	Time.hpp
)

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_HDR})
target_include_directories(${Name} PUBLIC .)
target_link_libraries(${Name} etl)
