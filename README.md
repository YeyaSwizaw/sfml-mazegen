SFML Maze Generator
===================

A simple maze generator, viewer, and solver written in C++ using SFML.

Compiling
---------

To compile, use premake4 to generate the makefile / project file as needed.
For example, with g++:

	premake4 gmake
	make

Requires a compiler with support for C++11 lambdas, <random> and for loops.
The only required library is SFML2

Usage
-----

To use, simply run the program.

'n' generates a new maze.
'1' chooses prims
'2' chooses recursive backtrack
'hjkl' or arrows choose size
's' solves the maze
