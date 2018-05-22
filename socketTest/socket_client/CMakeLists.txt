cmake_minimum_required(VERSION 3.7)
project(bomberman)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(bomberman ${SOURCE_FILES})
if(WIN32)
    target_link_libraries(bomberman wsock32 ws2_32)
endif()

find_package (Threads REQUIRED)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
# add_executable(${SOURCE_FILES})
