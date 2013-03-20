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

#include "inc/app.hpp"

MAZEVIEWER_NS_BEGIN

App::App() 
	: widthDialog(false), heightDialog(false), genRequested(false), solveRequested(false), solved(false) {

	font.loadFromFile("pf_ronda_seven.ttf");

} // App::App();

void App::init() {
	options.width = MAZEVIEWER_DEFAULT_GRIDSIZE;
	options.height = MAZEVIEWER_DEFAULT_GRIDSIZE;
	options.method = MAZEVIEWER_DEFAULT_METHOD;

	window.create(sf::VideoMode(MAZEVIEWER_GRIDSQUARE_SIZE * options.width, MAZEVIEWER_GRIDSQUARE_SIZE * options.height), "Maze Viewer");
		
	genRequested = true;

} // void App::init();

void App::loop() {
	while(window.isOpen()) {
		pollEvents();

		if(genRequested) {
			newMap();

		} // if(genRequested);
		if(solveRequested) {
			solve();

		} // if(solveRequested);

		window.clear();
		
		for(auto g : grid) {
			g.render(&window);

		} // for(auto g : grid);

		if(widthDialog || heightDialog) {
			d->render(&window);

		} // if(showWidthDialog || showHeightDialog);

		window.display();

	} // while(window.isOpen());

} // void App::loop();

void App::showWidthDialog() {
	d = new Dialog(window.getSize(), &font, DIALOG_WIDTH);

	widthDialog = true;

} // void App::showWidthDialog();

void App::showHeightDialog() {
	d = new Dialog(window.getSize(), &font, DIALOG_HEIGHT);

	heightDialog = true;

} // void App::showHeightDialog();

void App::newMap() {
	genRequested = false;
	solveRequested = false;
	solved = false;

	grid.clear();

	maze.generate(options);

	for(int i = 0; i < options.width; i++) {
		for(int j = 0; j < options.height; j++) {
			grid.push_back(GridSquare(i, j, maze.mazeGrid[i + (options.width) * j].walls));

		} // for(int j = 0; j < options.height; j++);

	} // for(int i = 0; i < options.width; i++);

	window.setSize(sf::Vector2u(MAZEVIEWER_GRIDSQUARE_SIZE * options.width, MAZEVIEWER_GRIDSQUARE_SIZE * options.height));
	window.setView(view = sf::View(sf::FloatRect(0, 0, MAZEVIEWER_GRIDSQUARE_SIZE * options.width, MAZEVIEWER_GRIDSQUARE_SIZE * options.height)));

} // void App::newMap();

void App::solve() {
	solveRequested = false;

	if(!solved) {
		grid.clear();

		maze.solve();

		for(int i = 0; i < options.width; i++) {
			for(int j = 0; j < options.height; j++) {
				grid.push_back(GridSquare(i, j, maze.mazeGrid[i + (options.width) * j].walls, maze.mazeGrid[i + options.width * j].inPath));

			} // for(int j = 0; j < options.height; j++);

		} // for(int i = 0; i < optiopns.width; i++);

	} // if(!solved);

	solved = true;

} // void App::solve();

MAZEVIEWER_NS_END

int main(int argc, char* argv[]) {
	MazeView::App a;
	a.init();
	a.loop();

} // int main(int argc, char* argv[]);
