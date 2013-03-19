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
File: src/inc/dialog.hpp
Author: Sam Sleight
***********/

#ifndef MAZEVIEWER_DIALOG_HPP
#define MAZEVIEWER_DIALOG_HPP

#include "defines.hpp"

#include <string>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

MAZEVIEWER_NS_BEGIN

enum DialogType {
	DIALOG_WIDTH,
	DIALOG_HEIGHT

}; // enum DialogType;

class Dialog {
public:
	Dialog() = default;
	Dialog(sf::Vector2u wndSize, sf::Font* font, int type);

	void enterNumber(sf::String num);
	void backspace();
	int getValue();

	void render(sf::RenderWindow* wndPtr);

private:
	int wndWidth, wndHeight;

	void updatePositions();

	sf::RectangleShape box;

	sf::Font *font;
	sf::Text text;

	sf::String value;

}; // class Dialog;

MAZEVIEWER_NS_END

#endif // MAZEVIEWER_DIALOG_HPP
