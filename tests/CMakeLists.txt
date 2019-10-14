cmake_minimum_required(VERSION 3.12)
project(WConsole)

set(CMAKE_CXX_STANDARD 14)

add_executable(tests tests.cpp)

target_include_directories(tests PUBLIC ${CMAKE_HOME_DIRECTORY}/include)
