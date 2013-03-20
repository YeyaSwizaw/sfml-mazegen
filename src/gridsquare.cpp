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
File: src/gridsquare.cpp
Author: Sam Sleight
***********/

#include "inc/gridsquare.hpp"

MAZEVIEWER_NS_BEGIN

GridSquare::GridSquare(int x, int y, bool walls[4], bool inPath)
	: xPos(x * MAZEVIEWER_GRIDSQUARE_SIZE), yPos(y * MAZEVIEWER_GRIDSQUARE_SIZE) {

	background.setPosition(xPos, yPos);
	background.setSize(sf::Vector2f(MAZEVIEWER_GRIDSQUARE_SIZE, MAZEVIEWER_GRIDSQUARE_SIZE));
	background.setFillColor(inPath ? sf::Color(70, 100, 150) : sf::Color(100, 100, 100));

	if(walls[NORTH]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos);
		lines.back().setSize(sf::Vector2f(MAZEVIEWER_GRIDSQUARE_SIZE, 1));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[NORTH]);

	if(walls[EAST]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos + MAZEVIEWER_GRIDSQUARE_SIZE - 1, yPos);
		lines.back().setSize(sf::Vector2f(1, MAZEVIEWER_GRIDSQUARE_SIZE));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[EAST]);

	if(walls[SOUTH]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos + MAZEVIEWER_GRIDSQUARE_SIZE - 1);
		lines.back().setSize(sf::Vector2f(MAZEVIEWER_GRIDSQUARE_SIZE, 1));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[SOUTH]);

	if(walls[WEST]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos);
		lines.back().setSize(sf::Vector2f(1, MAZEVIEWER_GRIDSQUARE_SIZE));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[WEST]);

} // GridSquare::GridSquare(int x, int y, int[4] walls);

void GridSquare::render(sf::RenderWindow *wndPtr) {
	wndPtr->draw(background);

	for(auto l : lines) {
		wndPtr->draw(l);

	} // for(auto l : lines);

} // void GridSquare::render(sf::RenderWindow *wndPtr);

MAZEVIEWER_NS_END
