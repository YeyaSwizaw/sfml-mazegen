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
	options.width = 20;
	options.height = 20;
	options.method = METHOD_PRIMS;

	window.create(sf::VideoMode(16 * options.width, 16 * options.height), "Maze Viewer");
		
	genRequested = true;

} // void App::init();

void App::loop() {
	sf::Event e;

	while(window.isOpen()) {
		while(window.pollEvent(e)) {
			if(e.type == sf::Event::Closed) {
				delete d;
				window.close();

			} // if(e.type == sf::Event::Closed);

			else if(e.type == sf::Event::KeyPressed) {
				if(widthDialog == false && heightDialog == false) {
					if(e.key.code == sf::Keyboard::Key::W) {
						showWidthDialog();

					} // if(e.key.code == sf::Keyboard::Key::W);
					else if(e.key.code == sf::Keyboard::Key::X) {
						showHeightDialog();

					} // else if(e.key.code == sf::Keyboard::Key::S);

					else if(e.key.code == sf::Keyboard::Key::N) {
						genRequested = true;

					} // if(e.key.code == sf::Keyboard::n);

					else if(e.key.code == sf::Keyboard::Key::S) {
						solveRequested = true;

					} // else if(e.key.code == sf::Keyboard:Key::S);

					else if(e.key.code == sf::Keyboard::Key::Num1) {
						options.method = METHOD_PRIMS;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::1);
					else if(e.key.code == sf::Keyboard::Key::Num2) {
						options.method = METHOD_RECURSIVE_BT;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::2);

					else if(e.key.code == sf::Keyboard::Key::K || e.key.code == sf::Keyboard::Key::Up) {
						options.height += 1;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::K || e.key.code == sf::Keyboard::Key::Up);
					else if(e.key.code == sf::Keyboard::Key::J || e.key.code == sf::Keyboard::Key::Down) {
						options.height -= 1;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::J || e.key.code == sf::Keyboard::Key::Down);

					else if(e.key.code == sf::Keyboard::Key::L || e.key.code == sf::Keyboard::Key::Right) {
						options.width += 1;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::L || e.key.code == sf::Keyboard::Key::Right);
					else if(e.key.code == sf::Keyboard::Key::H || e.key.code == sf::Keyboard::Key::Left) {
						options.width -= 1;
						genRequested = true;

					} // else if(e.key.code == sf::Keyboard::Key::H || e.key.code == sf::Keyboard::Key::Left);

				} // if(widthDialog == false && heightDialog == false);

				else {
					if(e.key.code == sf::Keyboard::Key::Return) {
						int val = d->getValue();

						if(val != 0) {
							if(widthDialog) {
								options.width = val;

							} // if(widthDialog);
							else {
								options.height = val;

							} // else;

							genRequested = true;

						} // if(val != 0);

						widthDialog = false;
						heightDialog = false;

						delete d;

					} // if(e.key.code == sf::Keyboad::Key::Enter);

					else if(e.key.code == sf::Keyboard::BackSpace) {
						d->backspace();

					} // else if(e.key.code == sf::Keyboard::Back);

				} // else;

			} // else if(e.type == sf::Event::KeyPressed);

			if(widthDialog || heightDialog) {
				if(e.type == sf::Event::TextEntered) {
					std::string val = sf::String(e.text.unicode).toAnsiString();
					std::string::const_iterator it = val.begin();
					while(it != val.end() && std::isdigit(*it)) {
						++it;

					} // while(it != val.end() && std::isdigit(*it));

					if(!val.empty() && it == val.end()) {
						d->enterNumber(sf::String(e.text.unicode));

					} // if(!val.empty() && it == val.end());

				} // if(e.type == sf::Event::TextEntered);

			} // if(widthDialog || heightDialog);

		} // while(window.pollEvent(e));

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

	window.setSize(sf::Vector2u(16 * options.width, 16 * options.height));
	window.setView(view = sf::View(sf::FloatRect(0, 0, 16 * options.width, 16 * options.height)));

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
