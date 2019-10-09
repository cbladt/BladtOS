set(Name BLibC)

SET (${Name}_SRC
    Assert.cpp
    String.cpp
)

SET (${Name}_HDR
    Assert.hpp
    String.hpp
)

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_HDR})
target_include_directories(${Name} PUBLIC .)
target_link_libraries(${Name} UtilityLib)
