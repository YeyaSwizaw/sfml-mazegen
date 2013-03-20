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
File: src/dialog.cpp
Author: Sam Sleight
***********/

#include "inc/dialog.hpp"

MAZEVIEWER_NS_BEGIN

Dialog::Dialog(std::string msg, sf::Vector2u wndSize, sf::Font* font)
	: MessageBox(msg, wndSize, font) {

} // Dialog::Dialog(std::string msg, sf::Vector2u wndSize, sf::Font* font);

void Dialog::enterNumber(sf::String num) {
	value.insert(value.getSize(), num);

	sf::String t = text.getString();
	t.insert(t.getSize(), num);
	text.setString(t);

	updatePositions();

} // void Dialog::enterNumber(Sf::string num);

void Dialog::backspace() {
	if(!value.isEmpty()) {
		value.erase(value.getSize() - 1);

		sf::String t = text.getString();
		t.erase(t.getSize() - 1);
		text.setString(t);

		updatePositions();

	} // if(!value.isEmpty());

} // void Dialog::backspace();

int Dialog::getValue() {
	std::string str = value.toAnsiString();

	int val;
	std::istringstream(str) >> val;

	return val;

} // int Dialog::getValue();

MAZEVIEWER_NS_END
