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
File: src/inc/gridsquare.hpp
Author: Sam Sleight
***********/

#ifndef MAZEVIEWER_GRIDSQUARE_HPP
#define MAZEVIEWER_GRIDSQUARE_HPP

#include "defines.hpp"
#include "maze.hpp"

#include <SFML/Graphics.hpp>

MAZEVIEWER_NS_BEGIN

class GridSquare {
public:
	GridSquare(int x, int y, bool walls[4], bool inPath = false);

	void render(sf::RenderWindow *wndPtr);

private:
	int xPos, yPos;

	sf::RectangleShape background;
	std::vector<sf::RectangleShape> lines;


}; // class GridSquare;

MAZEVIEWER_NS_END

#endif // MAZEVIEWER_GRIDSQUARE_HPP
