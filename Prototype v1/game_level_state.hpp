#ifndef GAME_LEVEL_STATE_HPP
#define GAME_LEVEL_STATE_HPP

#include <SFML\Graphics.hpp>

#include "game_state.hpp"
#include "map.hpp"


class GameLevel : public GameState {
private:
	sf::View levelView;
	sf::View hudView;

	Map map;

public:
	virtual void init();
	virtual void cleanUp();

	virtual void pause();
	virtual void resume();

	virtual void draw(const float dt);
	virtual void update(sf::Clock& clock);
	virtual void eventHandler();

	GameLevel(Game* game);
};

#endif // !GAME_LEVEL_STATE_HPP
