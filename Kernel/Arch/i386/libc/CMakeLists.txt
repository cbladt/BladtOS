SET (libc_SRC
	string.c
)

SET (libc_HDR
	string.h
	new
	_new.hpp
	assert.h
	stdlib.h	
)

add_library(libc STATIC ${libc_SRC} ${libc_HDR})
target_include_directories(libc PUBLIC .)
target_link_libraries(libc ArchLib)
