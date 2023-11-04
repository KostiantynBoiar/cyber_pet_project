cmake_minimum_required(VERSION 3.26)
project(cyber_pet_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(cyber_pet_project src/main.cpp
        src/headers/CSV.h
        src/source/CSV.cpp
        src/SFML-2.6.0-linux-gcc-64-bit/SFML-2.6.0/include/SFML/OpenGL.hpp
        src/source/Player.cpp
        src/headers/Player.h
        src/source/Game.cpp
        src/headers/Game.h)
