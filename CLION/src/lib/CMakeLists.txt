cmake_minimum_required(VERSION 3.7)
project(BomberMan)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES my_getnbr.c
                my_put_nbr.c
                my_putchar.c
                my_rand.c
                my_strcat.c
                my_string.c
                readline.c)

set(HEADER lib.h)

add_library(my_lib ${SOURCE_FILES} ${HEADER})