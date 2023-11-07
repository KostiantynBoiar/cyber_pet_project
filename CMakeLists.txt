cmake_minimum_required(VERSION 3.26)
project(cyber_pet_project)

set(CMAKE_CXX_STANDARD 17)
#src/SFML-2.6.0-linux-gcc-64-bit/SFML-2.6.0/include/SFML/OpenGL.hpp
add_executable(cyber_pet_project src/main.cpp

        src/source/Player.cpp
        src/headers/Player.h
        src/source/Game.cpp
        src/headers/Game.h
        src/source/JSON_API.cpp
        src/headers/JSON_API.h
        src/source/Button.cpp
        src/headers/Button.h
        src/source/Button.cpp
        src/headers/Button.h
)
