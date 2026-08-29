cmake_minimum_required(VERSION 3.10)
project(shooter-of-heck VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force CMake to look for ncurses, and not other curses
set(CURSES_NEED_NCURSES TRUE)

# Find the ncurses package
find_package(Curses REQUIRED)

# Define the executable (target) and its source files
add_executable(shooter
    src/main.c
)

if(MSVC)
    target_compile_options(shooter PRIVATE /W4 /WX)
else()
    target_compile_options(shooter PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Include the header directories found by CMake
target_include_directories(shooter PRIVATE ${CURSES_INCLUDE_DIRS})

# Link the ncurses library found by CMake
target_link_libraries(shooter PRIVATE ${CURSES_LIBRARIES})