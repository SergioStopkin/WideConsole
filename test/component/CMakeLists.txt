set(TARGET component-tests)

add_executable(${TARGET})
target_link_libraries(${TARGET} gtest gtest_main pthread)
target_include_directories(${TARGET} PUBLIC ${CMAKE_HOME_DIRECTORY}/include)

add_subdirectory(chart)
