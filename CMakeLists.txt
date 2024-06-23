cmake_minimum_required(VERSION 3.20)
project(cxxlox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(frontend)
add_subdirectory(tests)

add_executable(cxxlox Lox.cpp)

target_link_libraries(cxxlox PRIVATE Frontend)
