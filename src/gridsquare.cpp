#include "inc/gridsquare.hpp"

MAZEVIEWER_NS_BEGIN

GridSquare::GridSquare(int x, int y, bool walls[4], bool inPath)
	: xPos(x * 16), yPos(y * 16) {

	background.setPosition(xPos, yPos);
	background.setSize(sf::Vector2f(16, 16));
	background.setFillColor(inPath ? sf::Color(70, 100, 150) : sf::Color(100, 100, 100));

	if(walls[NORTH]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos);
		lines.back().setSize(sf::Vector2f(16, 1));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[NORTH]);

	if(walls[EAST]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos + 15, yPos);
		lines.back().setSize(sf::Vector2f(1, 16));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[EAST]);

	if(walls[SOUTH]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos + 15);
		lines.back().setSize(sf::Vector2f(16, 1));
		lines.back().setFillColor(sf::Color::Black);

	} // if(walls[SOUTH]);

	if(walls[WEST]) {
		lines.push_back(sf::RectangleShape());
		lines.back().setPosition(xPos, yPos);
		lines.back().setSize(sf::Vector2f(1, 16));
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
