#ifndef PLAYER_HPP
#define PLAYER_HPP

//#include <random>

#include "entity.hpp"


class Player : public Entity {
private:
	int health;
public:
	//player movement
	int moveSpeed;
	sf::Vector2f movePosition(sf::Keyboard::Key& dirKey);

	void takeDamage();
	bool isDead();


	Player(){}

	Player(sf::Vector2f& initialPos, sf::Texture& texture) {
		this->isSolid = true;
		this->type = entityType::PLAYER;
		this->health = 100;
		this->sprite.setOrigin(sf::Vector2f(0.0f, 0.0f));
		this->sprite.setPosition(initialPos);
		this->sprite.setTexture(texture);
	}

};

#endif // !PLAYER_HPP
