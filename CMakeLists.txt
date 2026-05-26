cmake_minimum_required(VERSION 3.16)
project(2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
set(SFML_LIB_DIR "${SFML_DIR}/lib")

add_executable(test 
    src/main.cpp
    src/Tile.cpp
    src/Game.cpp
    src/Config.cpp
    src/Data.cpp
)

target_include_directories(test PRIVATE
 "${SFML_INCLUDE_DIR}"
 "include"
)

target_link_directories(test PRIVATE "${SFML_LIB_DIR}")
target_compile_definitions(test PRIVATE SFML_STATIC)

target_link_libraries(test
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    
    freetype
    harfbuzz
    opengl32
    winmm
    gdi32
)