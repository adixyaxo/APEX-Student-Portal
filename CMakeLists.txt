cmake_minimum_required(VERSION 3.10)

project(STUDENT-API)
# Copies the directory content to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/templates DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/static DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(main main.cpp src/auth.cpp
    src/classes.cpp src/server.cpp )