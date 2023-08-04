cmake_minimum_required(VERSION 3.12)

message(STATUS "CMake version: ${CMAKE_VERSION}")

project(
    WideConsole
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
if(ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer -static-libasan"
    )# NOLINT(clang-diagnostic-error)
endif()

option(ENABLE_CLANG_FORMATTER "Use clang-formatter to format source code?" ON)

include_directories(${CMAKE_HOME_DIRECTORY}/include)

add_subdirectory(src)
add_subdirectory(test)
