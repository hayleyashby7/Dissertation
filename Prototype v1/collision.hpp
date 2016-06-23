#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML\Graphics.hpp>


class Collision {

	static bool checkCollision(sf::Vector2f position, Map& map);

	Collision();

};

#endif // !COLLISION_HPP
