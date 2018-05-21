cmake_minimum_required(VERSION 3.7)
project(BomberMan)
set(CMAKE_C_STANDARD 99)

add_subdirectory(src/lib)

set(SOURCE_FILES
        src/main.c
        src/team.c
        src/random_catch.c
        src/out_of_battle.c
        src/order.c
        src/mobs_attacks.c
        src/merchant.c
        src/init_sdl.c
        src/game.c
        src/display_annim.c
        src/creature_order.c
        src/attacks.c)

set(HEADERS src/bfm.h)

add_executable(BomberMan ${SOURCE_FILES} ${HEADERS})

target_link_libraries(BomberMan my_lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")

find_package (SDL)
find_package (SDL_ttf)
find_package (SDL_image)

if (SDL_FOUND AND SDLTTF_FOUND AND SDLIMAGE_FOUND)
    target_include_directories(BomberMan PUBLIC ${SDL_INCLUDE_DIR})
    target_include_directories(BomberMan PUBLIC ${SDLTTF_INCLUDE_DIR})
    target_include_directories(BomberMan PUBLIC ${SDLIMAGE_INCLUDE_DIR})
    target_link_libraries (BomberMan ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})

else ()
    message(FATAL_ERROR "SDL: not found")
endif ()
