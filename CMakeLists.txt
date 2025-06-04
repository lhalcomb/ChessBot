cmake_minimum_required(VERSION 3.10)
project(ChessBot)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to find Raylib if not found by default
set(CMAKE_PREFIX_PATH "/opt/homebrew")

# Find raylib via Homebrew installation
find_package(raylib REQUIRED)

# Include your own headers
include_directories(include)

# Create the executable from your source files
add_executable(ChessBot
    src/main.cpp 
    src/Game.cpp 
    src/Board.cpp 
    src/Move.cpp
    src/Evaluation.cpp 
    src/Search.cpp 
    src/InputHandler.cpp 
    src/Renderer.cpp
)

# Link Raylib and its required system frameworks (automatically handled)
target_link_libraries(ChessBot raylib)
