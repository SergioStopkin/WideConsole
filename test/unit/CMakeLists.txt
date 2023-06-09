set(TARGET unit-tests)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -fno-inline -fno-elide-constructors")

add_executable(
    ${TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/TestOne.cpp ${CMAKE_CURRENT_SOURCE_DIR}/TestTwo.cpp
              ${CMAKE_HOME_DIRECTORY}/src/ForGTest.cpp
)

target_include_directories(${TARGET} PRIVATE ${CMAKE_HOME_DIRECTORY}/src)

target_link_libraries(${TARGET} gtest gtest_main pthread)
