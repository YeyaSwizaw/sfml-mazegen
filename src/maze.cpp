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
File: src/maze.cpp
Author: Sam Sleight
***********/

#include "inc/maze.hpp"

MAZEVIEWER_NS_BEGIN

Maze::Maze() {

} // Maze::Maze();

void Maze::generate(MazeOptions options) {
	width = options.width;
	height = options.height;

	// Initialise grid.
	mazeGrid.clear();
	for(int i = 0; i <  width; i++) {
		for(int j = 0; j <  height; j++) {
			mazeGrid.push_back(Node());

		} // for(int j : height);

	} // for(int i : width);

	options.method == METHOD_PRIMS ? doPrims() : doRecursiveBacktrack();

} // void Maze::generate(MazeOptions options);

void Maze::doPrims() {
	std::default_random_engine engine(time(NULL));
	std::uniform_int_distribution<int> weightDist(100, 999);

	// Initialise edges 
	std::vector<Edge> edgeVect;
	for(int i = 0; i < mazeGrid.size(); i++) {
		// Horizontal edges
		if(i % width != (width - 1)) {
			edgeVect.push_back(Edge());
			edgeVect.back().from = i;
			edgeVect.back().to = i + 1;
			edgeVect.back().dir = EAST;

		} // if(i % width != (width - 1));

		// Vertical edges
		if(i < (mazeGrid.size() - width)) {
			edgeVect.push_back(Edge());
			edgeVect.back().from = i;
			edgeVect.back().to = i + width;
			edgeVect.back().dir = SOUTH;

		} // if(i < (mazeGrid.size() - width));

	} // for(int i = 0; i > mazeGrid.size() i++);

	// Assign random weights
	for(Edge& n : edgeVect) {
		n.weight = weightDist(engine);

	} // for(Edge& n : edgeVect);

	// Sort by weight
	std::sort(edgeVect.begin(), edgeVect.end(), [](const Edge& a, const Edge& b){ return a.weight < b.weight; });

	// Start at first node
	mazeGrid[0].inMaze = true;
	int nodeCount = 1;

	// Loop until n-1 edges in tree
	while(nodeCount < mazeGrid.size()) {
		for(Edge& n : edgeVect) {
			// Check if edge would create cycle
			if(mazeGrid[n.from].inMaze != mazeGrid[n.to].inMaze) {
				// Add node to maze
				mazeGrid[n.to].inMaze = true;
				mazeGrid[n.from].inMaze = true;
				nodeCount++;

				// Carve maze walls
				if(n.dir == EAST) {
					mazeGrid[n.from].walls[EAST] = false;
					mazeGrid[n.to].walls[WEST] = false;

				} // if(n.dir == EAST);
				else {
					mazeGrid[n.from].walls[SOUTH] = false;
					mazeGrid[n.to].walls[NORTH] = false;

				} // else;

				// Iterate over edges again
				break;

			} // if(mazeGrid[n.from].inMaze != mazeGrid[n.to].inMaze);

		} // for(Edge& n : edgeVect);

	} // while(nodeCount < mazeGrid.size());

	// If here, then done!

} // void Maze::doPrims();

void Maze::doRecursiveBacktrack() {
	srand(time(NULL));

	// Create direction list
	std::vector<int> dirs({NORTH, EAST, SOUTH, WEST});

	// Create vector of available nodes, starting with first node.
	std::vector<int> availableNodes({0});
	mazeGrid[0].inMaze = true;

	bool moved = false;
	bool moving = true;

	// Loop until back to start
	while(!availableNodes.empty()) {
		// Shuffle directions
		std::random_shuffle(dirs.begin(), dirs.end(), [](ptrdiff_t i){ return rand() % i; });

		// Attempt to travel each direction
		for(int dir : dirs) {
			// If north
			if(dir == NORTH && availableNodes.back() >= width) {
				// Check node isn't already in maze
				if(!mazeGrid[availableNodes.back() - width].inMaze) {
					// Add node to maze
					mazeGrid[availableNodes.back()].walls[NORTH] = false;
					mazeGrid[availableNodes.back() - width].walls[SOUTH] = false;
					mazeGrid[availableNodes.back() - width].inMaze = true;

					availableNodes.push_back(availableNodes.back() - width);

					// Successful move
					moved = true;
					moving = true;

					break;

				} // if(!mazeGrid[availableNodes.back() - width].inMaze);

			} // if(dir == NORTH && availableNodes.back() >= width);

			// If south
			else if(dir == SOUTH && availableNodes.back() < (mazeGrid.size() - width)) {
				// Check node isn't already in maze
				if(!mazeGrid[availableNodes.back() + width].inMaze) {
					// Add node to maze
					mazeGrid[availableNodes.back()].walls[SOUTH] = false;
					mazeGrid[availableNodes.back() + width].walls[NORTH] = false;
					mazeGrid[availableNodes.back() + width].inMaze = true;

					availableNodes.push_back(availableNodes.back() + width);

					// Successful move
					moved = true;
					moving = true;

					break;

				} // if(!mazeGrid[availableNodes.back() + width].inMaze);

			} // else if(dir == SOUTH && availableNodes.back() < (mazeGrid.size() - width));

			// If west
			else if(dir == WEST && (availableNodes.back() % width) != 0) {
				// Check node isn't already in maze
				if(!mazeGrid[availableNodes.back() - 1].inMaze) {
					// Add node to maze
					mazeGrid[availableNodes.back()].walls[WEST] = false;
					mazeGrid[availableNodes.back() - 1].walls[EAST] = false;
					mazeGrid[availableNodes.back() - 1].inMaze = true;

					availableNodes.push_back(availableNodes.back() - 1);

					// Successful move
					moved = true;
					moving = true;

					break;

				} // if(!mazeGrid[availableNodes.back() + width].inMaze);

			} // else if(dir == WEST && (availableNodes.back() % width) != 0);

			// If west
			else if(dir == EAST && (availableNodes.back() % width) != (width - 1)) {
				// Check node isn't already in maze
				if(!mazeGrid[availableNodes.back() + 1].inMaze) {
					// Add node to maze
					mazeGrid[availableNodes.back()].walls[EAST] = false;
					mazeGrid[availableNodes.back() + 1].walls[WEST] = false;
					mazeGrid[availableNodes.back() + 1].inMaze = true;

					availableNodes.push_back(availableNodes.back() + 1);

					// Successful move
					moved = true;
					moving = true;

					break;

				} // if(!mazeGrid[availableNodes.back() + width].inMaze);

			} // else if(dir == EAST && (availableNodes.back() % width) != (width - 1));

		} // for(int dir : dirs);

		// If no sucessful move
		if(!moved) {
			// Remove node from available list
			availableNodes.pop_back();

			moving = false;

		} // if(!moved);

		moved = false;

	} // while(!availableNodes.empty());

} // void Maze::doRecursiveBacktrack();

void Maze::solve() {
	srand(time(NULL));

	// Create direction list
	std::vector<int> dirs({NORTH, EAST, SOUTH, WEST});

	// Create path vector, and start in first node.
	std::vector<int> path;
	path.push_back(0);
	mazeGrid[path.back()].inPath = true;
	mazeGrid[path.back()].tried = true;

	bool moved = false;

	// Iterate until in bottom right corner
	while(path.back() != (width * height) - 1) {
		moved = false;

		// Shuffle dirs
		std::random_shuffle(dirs.begin(), dirs.end(), [](ptrdiff_t i){ return rand() % i; });

		for(int dir : dirs) {
			// Try to move in direction
			if(!mazeGrid[path.back()].walls[dir]) {
				if(dir == NORTH) {
					if(mazeGrid[path.back() - width].inPath == false && mazeGrid[path.back() - width].tried == false) {
						path.push_back(path.back() - width);
						mazeGrid[path.back()].inPath = true;
						mazeGrid[path.back()].tried = true;
						moved = true;

					} // if(mazeGrid[path.back() - width].inPath == false && mazeGrid[path.back() - width].tried == false);

				} // if(dir == NORTH);

				else if(dir == SOUTH) {
					if(mazeGrid[path.back() + width].inPath == false && mazeGrid[path.back() + width].tried == false) {
						path.push_back(path.back() + width);
						mazeGrid[path.back()].inPath = true;
						mazeGrid[path.back()].tried = true;
						moved = true;

					} // else if(mazeGrid[path.back() + width].inPath == false && mazeGrid[path.back() + width].tried == false);

				} // if(dir == NORTH);

				else if(dir == EAST) {
					if(mazeGrid[path.back() + 1].inPath == false && mazeGrid[path.back() + 1].tried == false) {
						path.push_back(path.back() + 1);
						mazeGrid[path.back()].inPath = true;
						mazeGrid[path.back()].tried = true;
						moved = true;

					} // if(mazeGrid[path.back() + 1].inPath == false && mazeGrid[path.back() + 1].tried == false);

				} // else if(dir == EAST);

				else if(dir == WEST) {
					if(mazeGrid[path.back() - 1].inPath == false && mazeGrid[path.back() - 1].tried == false) {
						path.push_back(path.back() - 1);
						mazeGrid[path.back()].inPath = true;
						mazeGrid[path.back()].tried = true;
						moved = true;

					} // if(mazeGrid[path.back() - 1].inPath == false && mazeGrid[path.back() - 1].tried == false);

				} // else if(dir == WEST);

			} // if(!mazeGrid[path.back()].walls[dir]);

			if(moved) {
				break;

			} // if(moved);

		} // for(int dir : dirs);

		if(!moved) {
			mazeGrid[path.back()].inPath = false;
			path.pop_back();

		} // if(!moved);

		moved = false;

	} // while(path.back() != (width * height) - 1);

} // void Maze::solve();

MAZEVIEWER_NS_END

