/*********
Copyright (c) 2013 Sam Sleight 

Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
THE SOFTWARE.
***********
Project: SFML Maze Generator
File: src/inc/maze.hpp
Author: Sam Sleight
***********/

#ifndef MAZEVIEWER_MAZE_HPP
#define MAZEVIEWER_MAZE_HPP

#include "defines.hpp"

#include <cstddef>
#include <ctime>
#include <random>
#include <algorithm>

MAZEVIEWER_NS_BEGIN

enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST

}; // enum Direction;

enum GenMethod {
	METHOD_PRIMS,
	METHOD_RECURSIVE_BT

}; // enum GenMethod;

struct MazeOptions {
	unsigned int width, height;
	GenMethod method;

}; // struct MazeOptions;

struct Node {
	bool walls[4], inMaze, inPath, tried;

	Node() : inMaze(false), inPath(false), tried(false) {
		walls[NORTH] = true;
		walls[EAST] = true;
		walls[SOUTH] = true;
		walls[WEST] = true;

	} // Node() : inMaze(false), inPath(false), tried(false);

}; // struct Node;

struct Edge {
	int from, to, weight;
	Direction dir;

};// struct Edge;

class Maze {
public:
	Maze();

	void generate(MazeOptions options);
	void solve();

	int width, height;
	std::vector<Node> mazeGrid;

private:
	void doPrims();
	void doRecursiveBacktrack();

}; // class Maze;

MAZEVIEWER_NS_END

#endif // MAZEVIEWER_MAZE_HPP
