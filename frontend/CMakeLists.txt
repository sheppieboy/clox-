set(SOURCES
    Scanner.cpp
)

set(HEADERS
    Scanner.hpp
    Token.hpp
)

add_library(Frontend ${SOURCES} ${HEADERS})

target_include_directories(Frontend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
