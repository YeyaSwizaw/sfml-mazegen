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
File: src/inc/events.hpp
Author: Sam Sleight
***********/

#include "inc/app.hpp"

MAZEVIEWER_NS_BEGIN

void App::pollEvents() {
	sf::Event e;
	while(window.pollEvent(e)) {
		if(e.type == sf::Event::Closed) {
			if(infoBox || widthDialog || heightDialog) {
				delete msgBox;

			} // if(infoBox);

			window.close();

		} // if(e.type == sf::Event::Closed);

		else if(e.type == sf::Event::KeyPressed) {
			if(widthDialog == false && heightDialog == false && infoBox == false) {
				if(e.key.code == sf::Keyboard::Key::W) {
					showWidthDialog();

				} // if(e.key.code == sf::Keyboard::Key::W);
				else if(e.key.code == sf::Keyboard::Key::X) {
					showHeightDialog();

				} // else if(e.key.code == sf::Keyboard::Key::S);
				else if(e.key.code == sf::Keyboard::Key::Return) {
					showInfoBox();

				} // else if(e.key.code == sf::Keyboard::Key::Return);
				else if(e.key.code == sf::Keyboard::Key::Slash) {
					showHelpBox();

				} // else if(e.key.code == sf::Keyboard::Key::Slash);

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
					if(widthDialog || heightDialog) {
						int val = static_cast<Dialog*>(msgBox)->getValue();

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

						delete msgBox;

					} // if(widthDialog || heightDialog);
					else {
						infoBox = false;

						delete msgBox;

					} // else;

				} // if(e.key.code == sf::Keyboad::Key::Enter);

				else if(e.key.code == sf::Keyboard::BackSpace) {
					if(widthDialog || heightDialog) {
						static_cast<Dialog*>(msgBox)->backspace();

					} // if(widthDialog || heightDialog);

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
					static_cast<Dialog*>(msgBox)->enterNumber(sf::String(e.text.unicode));

				} // if(!val.empty() && it == val.end());

			} // if(e.type == sf::Event::TextEntered);

		} // if(widthDialog || heightDialog);

	} // while(window.pollEvent(e));

} // void App::pollEvents();

MAZEVIEWER_NS_END
