set(TARGET component-tests)

add_executable(${TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp)

target_link_libraries(${TARGET} gtest gtest_main pthread)
