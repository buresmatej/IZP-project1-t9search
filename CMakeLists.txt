cmake_minimum_required(VERSION 4.3)
project(t9search C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(t9search t9search.c)

target_compile_options(t9search PRIVATE -Wall -Wextra -Werror -pedantic)
