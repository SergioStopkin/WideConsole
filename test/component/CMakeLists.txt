set(TARGET component-tests)

add_executable(${TARGET})
target_link_libraries(${TARGET} gtest gtest_main pthread)

add_subdirectory(chart)
add_subdirectory(graph)
