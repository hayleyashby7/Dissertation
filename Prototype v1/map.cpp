#include "map.hpp"


void Map::loadMap(const std::string& filename,unsigned int width, unsigned int height, 
	std::map<std::string, Tile>& entityAtlas, Game* game) {
	int totalSize = width * height;	
	std::ifstream input;
	input.open(filename);
	float currentX = 0;
	float currentY = 0;

	for (int i = 0; i <totalSize; i++)	
	{
		currentX = i % width;
		if (i % height == 0) currentY++;

		Cell cell(currentX, currentY);	

		char character;
		input.get(character);
		switch (character) {
		case '0':
			cell.cellContents.push_back(entityAtlas.at("floor"));
			break;
		case '1':
			cell.cellContents.push_back(entityAtlas.at("wall"));
			break;
		case '2': 
			player = Player(sf::Vector2f(currentX * this->tileSize, currentY* this->tileSize), game->texmgr.getRef("player"));			
			cell.cellContents.push_back(entityAtlas.at("floor"));					
			break;
		case '3':{
			Enemy enemy = Enemy(sf::Vector2f(currentX * this->tileSize, currentY* this->tileSize), game->texmgr.getRef("enemy"));
			
			enemies.push_back(enemy);
			cell.cellContents.push_back(entityAtlas.at("floor"));
		}
		default:
			break;
		}
		mapCells.push_back(cell);

	}
	input.close();
	return;
}

void Map::playerMove(sf::Keyboard::Key& dirKey) {	
	sf::Vector2f newPos = player.movePosition(dirKey);
	if (!checkCollision(newPos, this, player)) {
		player.updatePos(newPos);
	}
	
}

void Map::enemyMove() {
	for (auto &enemy : this->enemies) {
		sf::Vector2f newEnemyPos = enemy.movePosition(enemy.enemyDirection);
		if (!checkCollision(newEnemyPos, this, enemy)) {
			enemy.updatePos(newEnemyPos);
		}
		else {
			enemy.changeDirection();
		}
	}
}

bool Map::checkCollision(sf::Vector2f position, Map* map, Entity movingEntity) {
	position.x = position.x / tileSize;
	position.y = position.y / tileSize;

		for (auto &cell : map->mapCells) {
			if (cell.cellX == position.x && cell.cellY == position.y) {
				for (auto &content : cell.cellContents) {					
					if (content.type == Entity::entityType::WALL) {						
						return true;
					}
					if (movingEntity.type == Entity::entityType::PLAYER
						&& content.type == Entity::entityType::PICKUP) {
						//PICKUP
					}
				}
			}
		}
		if (movingEntity.type == Entity::entityType::ENEMY
			&& movingEntity.getPosition() == player.getPosition()) {
			player.takeDamage();
			this->gameOver = player.isDead();
		}
		return false;
}

void Map::draw(sf::RenderWindow& window) {

	for (auto &cell : this->mapCells) {
		for (auto &content : cell.cellContents){
			sf::Vector2f pos;
			pos.x = cell.cellX * content.tileSize;
			pos.y = cell.cellY * content.tileSize;
			content.sprite.setPosition(pos);
			content.draw(window);
		}
	}
	for (auto &enemy : this->enemies) {
		enemy.draw(window);
	}	
	player.draw(window);	
}