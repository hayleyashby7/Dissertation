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

	Player player;
	std::vector<Enemy> enemies;

	void loadMap(const std::string& filename, unsigned int width, unsigned int height, 
		std::map<std::string, Tile>& enemyAtlas, Game* thisGame);

	void playerMove(sf::Keyboard::Key& dirKey);
	void enemyMove();
	bool checkCollision(sf::Vector2f position, Map* map, Entity movingEntity);
	bool gameOver;
	bool playerHit;

	void draw(sf::RenderWindow& window);

	Map() {		
		this->width = 0;
		this->height = 0;
		this->tileSize = 0;
		this->gameOver = false;
		this->playerHit = false;
	}

	Map(const std::string& filename, unsigned int width, unsigned int height, unsigned int tileSize, 
		std::map<std::string, Tile>& tileAtlas, Game* game) {
		this->width = width;
		this->height = height;
		this->tileSize = tileSize;
		loadMap(filename, width, height, tileAtlas, game);
		this->gameOver = false;
	}
};

#endif // !MAP_HPP
