# shooter-of-heck
This game is a recreation of a game I made in GDevelop, [Shooter of hell](https://youtu.be/RcWbtofICvA).
## Build it
Dependencies are `git cmake gcc/clang/msvc`
To run it, run
```
git clone https://github.com/charlesjchai/shooter-of-heck
cd shooter-of-heck
cmake -B build
cmake --build build
./build/shooter
```
## Help
If you are running windows, you may need to change ncurses to pdcurses in [CMakeLists.txt](CMakeLists.txt) and in [src/curses.h](src/curses.h)

## Acknowledgements
- ncurses
- miniaudio