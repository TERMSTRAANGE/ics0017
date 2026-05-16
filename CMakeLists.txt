cmake_minimum_required(VERSION 3.10)
project(ics0017 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/card.cpp
    src/deck.cpp
    src/player.cpp
    src/game.cpp
    src/utils.cpp
    src/exceptions.cpp
    src/ui.cpp
    src/persistence.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
