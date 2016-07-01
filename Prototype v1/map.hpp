#ifndef MAP_HPP
#define MAP_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

#include "tile.hpp"
#include "game.hpp"
#include "cell.hpp"
#include "player.hpp"
#include "enemy.hpp"


class Map {

public:
	int height;
	int width;
	int tileSize;
	
	std::vector<Cell> mapCells;

	std::vector<Enemy> enemies;

	void loadMap(const std::string& filename, unsigned int width, unsigned int height, 
		std::map<std::string, Tile>& enemyAtlas, Game* game, Player& player);

	
	void enemyMove(Player& player);
	bool checkCollision(sf::Vector2f position, Entity movingEntity);

	void draw(sf::RenderWindow& window);

	Map() {		
		this->width = 0;
		this->height = 0;
		this->tileSize = 0;
	}

	Map(const std::string& filename, unsigned int width, unsigned int height, unsigned int tileSize,
		std::map<std::string, Tile>& tileAtlas, Game* game, Player& player) {
		this->width = width;
		this->height = height;
		this->tileSize = tileSize;
		loadMap(filename, width, height, tileAtlas, game, player);
	}
};

#endif // !MAP_HPP
