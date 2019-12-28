cmake_minimum_required(VERSION 3.14)
project(scripting_comparison)

set(CMAKE_CXX_STANDARD 17)

add_library(harness STATIC main.cpp)

add_executable(st_lua_jit lua_harness.cpp)
target_compile_definitions(st_lua_jit PRIVATE JIT)
target_link_libraries(st_lua_jit PRIVATE harness ${CMAKE_SOURCE_DIR}/moonjit/src/libluajit.a dl)

add_executable(st_lua lua_harness.cpp)
target_link_libraries(st_lua PRIVATE harness /usr/lib/x86_64-linux-gnu/liblua5.1.a dl)
