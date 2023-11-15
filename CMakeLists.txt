cmake_minimum_required(VERSION 3.26)
project(cyber_pet_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(
        ${SFML_INCLUDE_DIRS}
        /home/kostiantyn/Documents/education/C/cyber-pet-project/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include/SFML
        /usr/x86_64-w64-mingw32/include/rapidjson
)

set(SOURCES
        linux-edition/src/main.cpp
        linux-edition/src/source/Player.cpp
        linux-edition/src/source/Game.cpp
        linux-edition/src/source/JSON_API.cpp
        linux-edition/src/source/Button.cpp
)

add_executable(cyber_pet_project WIN32 ${SOURCES})

target_link_libraries(cyber_pet_project PRIVATE sfml-graphics sfml-window sfml-system)