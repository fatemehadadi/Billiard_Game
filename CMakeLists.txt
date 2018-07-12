cmake_minimum_required(VERSION 3.2)
project(Bill)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/renderer.h headers/game.h sources/game.cpp headers/ball.h sources/ball.cpp sources/player.cpp headers/player.h headers/color.h sources/color.cpp)
add_executable(Bill ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Bill ${SFML_LIBRARIES})
endif()
