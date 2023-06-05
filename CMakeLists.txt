cmake_minimum_required(VERSION 3.8)

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(
    WConsole
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
if(ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer -static-libasan") # NOLINT(clang-diagnostic-error)
endif()

option(ENABLE_CLANG_FORMATTER "Use clang-formatter to format source code?" ON)

add_subdirectory(src)
add_subdirectory(test)
