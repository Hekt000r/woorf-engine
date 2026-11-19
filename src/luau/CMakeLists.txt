cmake_minimum_required(VERSION 3.15)
project(woorf_luau CXX)

add_subdirectory(vendor)

add_executable(woorf_luau LuauConnector.cpp)
target_link_libraries(woorf_luau PRIVATE Luau.VM Luau.Compiler)