#ifndef MAZEVIEWER_APP_HPP
#define MAZEVIEWER_APP_HPP

#include "defines.hpp"
#include "maze.hpp"
#include "gridsquare.hpp"

#include <SFML/Graphics.hpp>

MAZEVIEWER_NS_BEGIN

class App {
public:
	App();

	void init();
	void loop();

private:
	MazeOptions options;
	Maze maze;

	std::vector<GridSquare> grid;

	sf::View view;
	sf::RenderWindow window;

	void newMap();

	bool solved;
	void solve();

}; // class App;

MAZEVIEWER_NS_END

#endif // MAZEVIEWER_APP_HPP
