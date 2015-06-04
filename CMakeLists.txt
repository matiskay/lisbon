cmake_minimum_required(VERSION 3.2)
project(lisbon)

# What is the difference between static and something else.
add_library(graph STATIC graph.c)

add_executable(lisbon main.c)
target_link_libraries(lisbon graph)

add_executable(test_graph test_graph.c)
target_link_libraries(test_graph graph)

install(TARGETS lisbon DESTINATION bin)
