cmake_minimum_required(VERSION 3.26)
project(cyber_pet_project)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

set(SOURCES
        src/main.cpp
        src/source/Player.cpp
        src/source/Game.cpp
        src/source/JSON_API.cpp
        src/source/Button.cpp
)

add_executable(cyber_pet_project ${SOURCES})

target_link_libraries(cyber_pet_project PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    target_compile_options(cyber_pet_project PRIVATE /EHsc)

    add_custom_command(TARGET cyber_pet_project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_DIR}/../../../bin"
            $<TARGET_FILE_DIR:cyber_pet_project>)
endif()
