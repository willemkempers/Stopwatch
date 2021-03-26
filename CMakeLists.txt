cmake_minimum_required(VERSION 3.12.1 FATAL_ERROR)
project(stopwatch VERSION 0.1.0)
add_library(stopwatch INTERFACE)
target_include_directories(stopwatch INTERFACE include)