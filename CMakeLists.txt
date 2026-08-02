cmake_minimum_required(VERSION 3.10)
project(minesweeper-ncurses VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Force CMake to look for ncurses, and not other curses
set(CURSES_NEED_NCURSES TRUE)

# Find the ncurses package
find_package(Curses REQUIRED)

# Define the executable (target) and its source files
add_executable(minesweeper
    src/main.c
)

# Include the header directories found by CMake
target_include_directories(minesweeper PRIVATE ${CURSES_INCLUDE_DIRS})

# Link the ncurses library found by CMake
target_link_libraries(minesweeper PRIVATE ${CURSES_LIBRARIES})