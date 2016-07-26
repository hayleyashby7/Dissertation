#include "game_state.hpp"
#include "game_level_state.hpp"
#include "main_menu_state.hpp"
#include "info_state.hpp"
#include "map.hpp"


void GameLevel::init() {
	this->game->window.clear(sf::Color::Black);
	this->game->background.setTexture(this->game->texmgr.getRef("background"));
	this->game->window.draw(this->game->background);
	map.draw(this->game->window);
	audmgr.loadSoundBuffer("pickup", "assets/sounds/pickup.wav");
	audmgr.loadSoundBuffer("playerHit", "assets/sounds/playerhit.wav");
	audmgr.loadSoundBuffer("unlockDoor", "assets/sounds/unlockdoor.wav");	
}
void GameLevel::cleanUp(){}
void GameLevel::pause(){}
void GameLevel::resume(){}

void GameLevel::draw(const float dt) {
	this->game->window.clear(sf::Color::Black);	
	this->game->window.draw(this->game->background);	
	map.draw(this->game->window);
	gui.draw(this->game->window);
	player.draw(this->game->window);
	return;
}

void GameLevel::update(sf::Clock& clock) {
	/*Check Game Over*/
	if (this->gameOver) {
		this->game->changeState(new MainMenu(this->game));
	}

	/*Check if progressed level*/
	if (this->map.nextLevel) {
		this->map.prevVisited = true;
		if (prevLevels.size() >= this->map.id) {
			prevLevels[currentLevel - 1] = this->map;
		}
		else {
			prevLevels.push_back(this->map);
		}
		currentLevel++;
		if (currentLevel > maxLevel) {
			gameOver = true;
		}
		else {	
			bool previous = false;
			for (auto& oldMap : prevLevels) {
				if (oldMap.prevVisited && oldMap.id == currentLevel) {
					this->map = oldMap;
					this->map.restartMap(player);
					previous = true;
					break;
				}
			}				
			if (!previous) {
				std::string file = "map" + std::to_string(currentLevel);
				map = Map(mapFiles[file], currentLevel, 15, 15, 32, game->tileAtlas, game, player);
				mapList[file] = map;
				this->gui.update("level", "Level: " + std::to_string(currentLevel));
			}
			
		}
		map.nextLevel = false;		
	}

	/*Check if regressed level*/
	if (this->map.prevLevel) {
		this->map.prevVisited = true;
		if (prevLevels.size() >= currentLevel) {
			prevLevels[currentLevel - 1] = this->map;
		}
		else {
			prevLevels.push_back(this->map);
		}		
		if (currentLevel > 1) {
			currentLevel--;
		}
		map = prevLevels[currentLevel-1];
		this->gui.update("level", "Level: " + std::to_string(currentLevel));
		map.returnMap(player);
		
	}

	/*Enemy movement*/
	float dt = clock.getElapsedTime().asSeconds();
	if (dt > this->game->gameSpeed) {
		this->map.enemyMove(player);
		if (this->player.beenHit) {
			this->gui.update("player", "Health: " + this->player.getHealth());
			this->gui.update("key", "Keys Gathered: " + this->player.getKeys());
		}
		gameOver = player.isDead();
		this->player.beenHit = false;
	}	
	
	

	return;
}

void GameLevel::eventHandler() {
	sf::Event event;

	while (this->game->window.pollEvent(event)) {
		
		switch (event.type) {

			/*Window closed*/
		case sf::Event::Closed: {
			game->window.close();
			break;
		}

		/*Key Pressed*/
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Q) {
				game->window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::B) {
				this->game->goBackState();
				break;
			}

			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A ||
				event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
				sf::Keyboard::Key k = event.key.code;
				this->playerMove(k);				
			}	
			if (event.key.code == sf::Keyboard::Return) {
				if (this->player.TNT > 0) {
					this->map.TNT(this->player);
					this->gui.update("tnt", "TNT: " + std::to_string(this->player.TNT));
				}				
			}
		}								
		default:
			break;
		}

	}

}

void GameLevel::playerMove(sf::Keyboard::Key& dirKey) {
	int mapKeys = map.keys;
	sf::Vector2f newPos = player.movePosition(dirKey);
	if (!map.checkCollision(newPos, player)) {
		player.updatePos(newPos);
	}
	if (map.keys < mapKeys) {
		player.keys++;
		this->gui.update("key", "Keys Gathered: " + this->player.getKeys());
		sf::SoundBuffer pickupBuf;
		pickupBuf.loadFromFile("assets/sounds/pickup.wav");
		sf::Sound pickupSound;
		pickupSound.setBuffer(pickupBuf);
		pickupSound.setVolume(50);
		this->game->bgMusic.pause();
		pickupSound.play();
		this->game->bgMusic.play();
	}

	if (this->player.beenHit) {
		this->gui.update("player", "Health: " + this->player.getHealth());		
	}

	gameOver = player.isDead();
	this->player.beenHit = false;

}

GameLevel::GameLevel(Game* game) {
	player = Player(sf::Vector2f(0, 0), game->texmgr.getRef("player"));
	this->game = game;
	this->player = player;
	this->game->bgMusic.openFromFile("assets/sounds/level.wav");
	this->game->bgMusic.play();

	std::random_device rd;
	std::mt19937 generator(rd());
	std::bernoulli_distribution bd(0.5);

	noveltySearch = bd(generator);
	if (noveltySearch) {
		this->code = "TC_NS";
	}
	else {
		this->code = "TC_FF";
	}

	for (int i = 1; i < 7; i++) {
		std::string filename;
		if (noveltySearch) {
			filename = "assets/maps/NS/map" + std::to_string(i) + ".dat";
		}
		else {
			filename = "assets/maps/FF/map" + std::to_string(i) + ".dat";
		}
			std::string mapName = "map" + std::to_string(i);
			mapFiles[mapName] = filename;		
	}
	
	currentLevel = 1;
	map = Map(mapFiles["map1"], currentLevel, 15,15,32, game->tileAtlas, game, player, true);
	mapList["map1"] = map;
	this->gui.update("level", "Level: " + std::to_string(currentLevel));
	this->gui.update("code", this->code);
	this->gui.update("tnt", "TNT: " + std::to_string(this->player.TNT));

}