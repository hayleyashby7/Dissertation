#include "map.hpp"


void Map::loadMap(const std::string& filename,unsigned int width, unsigned int height, 
	std::map<std::string, Tile>& entityAtlas, Game* game, Player& player) {
	int totalSize = width * height;	
	std::ifstream input;
	input.open(filename);
	float currentX = 0;
	float currentY = 0;

	for (int i = 0; i <totalSize; i++)	
	{
		currentX = i % width + 1;
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
		case '2': {
			Enemy enemy = Enemy(sf::Vector2f(currentX * this->tileSize, currentY* this->tileSize), game->texmgr.getRef("enemy"));

			enemies.push_back(enemy);
			cell.cellContents.push_back(entityAtlas.at("floor"));
		}
		case '3':
			//pickup
			cell.cellContents.push_back(entityAtlas.at("floor"));

		case '4': 
			player.setPosition(sf::Vector2f(currentX * this->tileSize, currentY* this->tileSize));
			cell.cellContents.push_back(entityAtlas.at("floor"));					
			break;
		case '5':
			//exit
			cell.cellContents.push_back(entityAtlas.at("floor"));
		
		default:
			break;
		}
		mapCells.push_back(cell);

	}
	input.close();
	return;
}

void Map::enemyMove(Player &player) {
	for (auto &enemy : this->enemies) {
		sf::Vector2f newEnemyPos = enemy.movePosition(enemy.enemyDirection);
		if (!checkCollision(newEnemyPos, enemy)) {
			enemy.updatePos(newEnemyPos);
			if (newEnemyPos == player.getPosition()) {
				player.takeDamage();
			}
		}
		else {
			enemy.changeDirection();
		}
	}
}

bool Map::checkCollision(sf::Vector2f position, Entity movingEntity) {
	position.x = position.x / tileSize;
	position.y = position.y / tileSize;

	//check out of bounds
	if (position.x <=0 || position.x > 15
		|| position.y <= 0 || position.y > 15) {
		return true;
	}
	
	//check collisions within map
	for (auto &cell : this->mapCells) {
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
	if (movingEntity.type == Entity::entityType::PLAYER) {
		for (auto &enemy : this->enemies) {
			if (enemy.getPosition() == movingEntity.getPosition()) {
				movingEntity.takeDamage();
			}

		}
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
	//
}