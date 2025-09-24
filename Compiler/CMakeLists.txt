cmake_minimum_required(VERSION 3.31)
project(Practice3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Practice3
        main.c
        parser_LL.c
        parser_RDCP.c
        scanner.c)
