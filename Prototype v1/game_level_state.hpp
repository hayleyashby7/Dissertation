#ifndef GAME_LEVEL_STATE_HPP
#define GAME_LEVEL_STATE_HPP

#include <SFML\Graphics.hpp>
#include <map>
#include <random>

#include "game_state.hpp"
#include "map.hpp"
#include "gui.hpp"
#include "player.hpp"


class GameLevel : public GameState {
private:
	
	Map map;
	Gui gui;
	std::map<std::string, std::string> mapFiles;
	std::map<std::string, Map> mapList;
	bool noveltySearch;
	int currentLevel;

public:
	Player player;
	bool gameOver;

	void playerMove(sf::Keyboard::Key& dirKey);
	
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
