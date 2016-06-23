#ifndef CELL_HPP
#define CELL_HPP

#include <vector>

#include "entity.hpp"

class Cell {
public:
	std::vector<Entity> cellContents;

	int cellX;
	int cellY;
	int tileSize = 32;

	sf::Vector2f getPosition() {
		sf::Vector2f position;
		position.x = cellX * tileSize;
		position.y = cellY * tileSize;
	}

	Cell(const int& x, const int& y) {
		this->cellX = x;
		this->cellY = y;
	}
	

};

#endif // !CELL_HPP