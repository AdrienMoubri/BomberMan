cmake_minimum_required(VERSION 3.7)
project(CLION_s)
set(CMAKE_C_STANDARD 11)

include_directories ("${PROJECT_SOURCE_DIR}/src/lib")

set(SOURCE_FILES
        src/team.c
        src/random_catch.c
        src/out_of_battle.c
        src/order.c
        src/mobs_attacks.c
        src/merchant.c
        src/main.c
        src/init_sdl.c
        src/game.c
        src/display_annim.c
        src/creature_order.c
        src/attacks.c)

add_executable(BomberMan ${SOURCE_FILES})

add_library(lib ${PROJECT_SOURCE_DIR}/src/lib/readline.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_string.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_strcat.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_rand.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_getnbr.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_put_nbr.c
                ${PROJECT_SOURCE_DIR}/src/lib/my_putchar.c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")

find_package (SDL)
find_package (SDL_ttf)
find_package (SDL_image)
if (SDL_FOUND AND SDL_ttf_FOUND AND SDL_image_FOUND)
    target_include_directories(bomberman PUBLIC ${SDL_INCLUDE_DIR})
    target_link_libraries (bomberman ${SDL_LIBRARY})
    target_include_directories(bomberman PUBLIC ${SDL_ttf_INCLUDE_DIR})
    target_link_libraries (bomberman ${SDL_ttf_LIBRARY})
    target_include_directories(bomberman PUBLIC ${SDL_image_INCLUDE_DIR})
    target_link_libraries (bomberman ${SDL_image_LIBRARY})
else ()
    message(FATAL_ERROR "SDL: not found")
endif ()