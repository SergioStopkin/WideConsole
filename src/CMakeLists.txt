#set(TARGET ${PROJECT_NAME})
set(TARGET wconsole)

add_executable(${TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(${TARGET} PUBLIC ${CMAKE_HOME_DIRECTORY}/include)
