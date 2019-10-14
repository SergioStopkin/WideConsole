cmake_minimum_required(VERSION 3.12)
project(WConsole)

set(CMAKE_CXX_STANDARD 14)

add_executable(wconsole main.cpp)

target_include_directories(wconsole PUBLIC ${CMAKE_HOME_DIRECTORY}/include)
