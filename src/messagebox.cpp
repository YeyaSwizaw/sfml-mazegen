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
File: src/messagebox.cpp
Author: Sam Sleight
***********/

#include "inc/messagebox.hpp"

MAZEVIEWER_NS_BEGIN

MessageBox::MessageBox(std::string msg, sf::Vector2u wndSize, sf::Font* font) {
	wndWidth = wndSize.x;
	wndHeight = wndSize.y;

	this->font = font;
	text.setFont(*font);
	text.setCharacterSize(16);
	text.setColor(sf::Color::Black);
	text.setString(msg);

	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Black);
	box.setFillColor(sf::Color::White);

	updatePositions();

} // MessageBox::MessageBox(std::string msg, sf::Vector2u wndSize, sf::Font* font);

void MessageBox::render(sf::RenderWindow* wndPtr) {
	wndPtr->draw(box);
	wndPtr->draw(text);

} // void MessageBox::render(sf::RenderWindow* wndPtr);

void MessageBox::updatePositions() {
	text.setPosition((wndWidth / 2) - (text.getLocalBounds().width / 2), (wndHeight / 2) - (text.getLocalBounds().height / 2));

	box.setSize(sf::Vector2f(text.getLocalBounds().width + 32, text.getLocalBounds().height + 32));
	box.setPosition((wndWidth / 2) - (box.getSize().x / 2), (wndHeight / 2) - (box.getSize().y / 2));

} // void MessageBox::updatePositions();

MAZEVIEWER_NS_END
