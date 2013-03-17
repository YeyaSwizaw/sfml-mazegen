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
