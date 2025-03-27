cmake_minimum_required(VERSION 3.10)
project(ChessBot)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

include_directories(include)

add_executable(ChessBot
    src/main.cpp 
    src/Game.cpp 
    src/Board.cpp 
    src/Move.cpp
    src/Evaluation.cpp 
    src/Search.cpp 
    src/InputHandler.cpp 
    src/Renderer.cpp
    src/PreCompMoveData.cpp
)

target_link_libraries(ChessBot raylib)
