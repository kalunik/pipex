cmake_minimum_required(VERSION 3.20)
project(push_swap LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include_directories(includes/)

add_executable(
        pipex
        pipex.c
        main.c
)