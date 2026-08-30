# shooter-of-heck

This game is a recreation of a game I made in GDevelop, [Shooter of hell](https://youtu.be/RcWbtofICvA) , the source code can be found [here](https://drive.google.com/drive/folders/1DRBop1QIdV54oIM8mhQnP0xCDJb1n2gq?usp=sharing).

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

If you are running Windows, you may need to change ncurses to pdcurses in [CMakeLists.txt](CMakeLists.txt) and in [headerz.h](include/headerz.h)

## Acknowledgements

- ncurses
- miniaudio
