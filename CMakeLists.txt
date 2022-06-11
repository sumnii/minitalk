cmake_minimum_required(VERSION 3.22)
project(minitalk C)

set(CMAKE_C_STANDARD 99)

add_executable(minitalk client.c server.c)
