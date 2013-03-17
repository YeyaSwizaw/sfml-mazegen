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
