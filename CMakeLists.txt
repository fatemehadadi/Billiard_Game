cmake_minimum_required(VERSION 3.2)
project(snooker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/renderer.h headers/game.h headers/player.h headers/ball.h headers/network.h sources/game.cpp sources/ball.cpp sources/player.cpp headers/resource.h sources/resource.cpp sources/network.cpp)
add_executable(snooker ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(snooker ${SFML_LIBRARIES})
endif()
