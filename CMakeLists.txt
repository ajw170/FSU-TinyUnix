cmake_minimum_required(VERSION 3.12)
project(TinyUnix C)

set(CMAKE_C_STANDARD 99)
set(FLAGS  "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS  "${FLAGS}")

add_executable(TinyUnix shell.c)