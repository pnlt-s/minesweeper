cmake_minimum_required(VERSION 3.26)
project(sweeper C)

set(CMAKE_C_STANDARD 23)

add_executable(sweeper main.c
        sweeper.h
        sweeper.c)
