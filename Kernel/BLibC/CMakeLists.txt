set(Name BLibC)

set(${Name}_SRC
    Assert.cpp
    String.cpp
)

set(${Name}_HDR
    Assert.hpp
    String.hpp
)

add_library(${Name} STATIC ${${Name}_SRC} ${${Name}_HDR})
target_include_directories(${Name} PUBLIC .)
