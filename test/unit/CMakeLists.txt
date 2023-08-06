set(TARGET unit-tests)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -fno-inline -fno-elide-constructors")

add_executable(${TARGET})
target_link_libraries(${TARGET} gtest gtest_main pthread)

add_subdirectory(tool)
