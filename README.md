# WaveFunctionCollapse

## Prerequisites

- [CMake](https://cmake.org/)
- [CImg](http://cimg.eu/)

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Setup

Put tiles and tileset.cfg in the `./res/` folder.

- 0.png is the up tile.
- 1.png is the right tile.
- 2.png is the down tile.
- 3.png is the left tile.
- 4.png is the empty tile.

tileset.cfg example:

```
0.png 1 1 0 1
1.png 1 1 1 0
2.png 0 1 1 1
3.png 1 0 1 1
4.png 0 0 0 0
```
where the numbers are the tile's connections, in the same order as tile name.
## Run

```bash
./wavefunctioncollapse <size of output image> <path to tileset folder>
```