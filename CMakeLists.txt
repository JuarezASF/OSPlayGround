cmake_minimum_required(VERSION 3.3)
project(OSPlayGround)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(OSPlayGround ${SOURCE_FILES})

add_executable(fork_sample fork/main.cpp)

add_executable(exec_sample0 exec/p0.cpp)
add_executable(exec_sample1 exec/p1.cpp)

add_executable(pipe_sample pipe/main.cpp)

add_executable(msg_queue_sample msg_queue/main.cpp)
