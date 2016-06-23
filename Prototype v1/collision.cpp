#include "collision.hpp"

bool Collision::checkCollision(sf::Vector2f position, Map* map) {
	for (auto &cell : map->mapCells) {
		if (cell.cellX == position.x && cell.cellY == position.y) {
			for (auto &content : cell.cellContents) {
				if (content.isSolid) {
					return true;
				}
			}
		}
	}
	return false;
}