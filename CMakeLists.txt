cmake_minimum_required(VERSION 3.26)
project(cyber_pet_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

include_directories(/usr/include)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES
        src/main.cpp
        src/source/Player.cpp
        src/headers/Player.h
        src/source/Game.cpp
        src/headers/Game.h
        src/source/JSON_API.cpp
        src/headers/JSON_API.h
        src/source/Button.cpp
        src/headers/Button.h
)

add_executable(cyber_pet_project ${SOURCES})

target_link_directories(cyber_pet_project PRIVATE /usr/include/SFML)

target_link_libraries(cyber_pet_project PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    target_compile_options(cyber_pet_project PRIVATE /EHsc)

    add_custom_command(TARGET cyber_pet_project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "/usr/lib"
            $<TARGET_FILE_DIR:cyber_pet_project>)
endif()
