# C++ 8-puzzle

---

## Overview

The is a simple solver (c++) to complete the 8-puzzle problem by finding the optimal path with A* algorithm. A class is create call BoardNode which contains all the functions that are needed.


## Pre-request

- cmake
- googletest
- git

## Standard install and Build via command-line
```
git clone --recursive https://github.com/zzjkf2009/8-puzzle
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```
## Result
### Possible Nodes
All the possible nodes are stored in the StoreAllNodes.txt file (One example is placed at Result folder, the new auto generated is located at 'build' folder)
### Solutions
The path will be printed on the screen(terminal) in the **reversed oder** (goal -> start).Some screen shots of solutions are also displaced in the Result folder, some of the puzzles take less steps to solve, some of them may takes more steps.
