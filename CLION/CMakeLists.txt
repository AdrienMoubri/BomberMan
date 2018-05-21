cmake_minimum_required(VERSION 3.7)
project(BomberMan)
set(CMAKE_C_STANDARD 99)

add_subdirectory(src/lib)

set(SOURCE_FILES
        src/main.c
        src/team.c
        src/order.c
        src/init_sdl.c
        src/game.c
        src/bombes.c
        src/Engine.c
        src/heroes_images.c
        src/drawer.c
        src/socket.c)

link_libraries (
        ${SDL_LIBRARY}
        ${SDLIMAGE_LIBRARY}
        ${SDLTTF_LIBRARY}
)

set(HEADERS src/bfm.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} my_lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")

find_package (SDL)
find_package (SDL_ttf)
find_package (SDL_image)
find_package(Threads REQUIRED)


if (SDL_FOUND AND SDL_TTF_FOUND AND SDL_IMAGE_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${SDL_LIBRARY})
    target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_TTF_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries (${PROJECT_NAME} ${SDL_TTF_LIBRARY})
    target_include_directories(${PROJECT_NAME} PUBLIC ${SDL_IMAGE_INCLUDE_DIR} )
    target_link_libraries (${PROJECT_NAME} ${SDL_IMAGE_LIBRARY})
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
    endif()
else ()
    message(FATAL_ERROR "SDL: not found")
endif ()