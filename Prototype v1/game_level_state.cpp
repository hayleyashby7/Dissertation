#include "game_state.hpp"
#include "game_level_state.hpp"
#include "main_menu_state.hpp"
#include "map.hpp"


void GameLevel::init() {
	this->game->window.clear(sf::Color::Black);
	this->game->background.setTexture(this->game->texmgr.getRef("background"));
	this->game->window.draw(this->game->background);
	map.draw(this->game->window);
	
}
void GameLevel::cleanUp() {}
void GameLevel::pause() {}
void GameLevel::resume() {}

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

	/*Enemy movement*/
	float dt = clock.getElapsedTime().asSeconds();
	if (dt > this->game->gameSpeed) {
		this->map.enemyMove(player);
		if (this->player.beenHit) {
			this->gui.update("player", "Health: " + this->player.getHealth());			
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
			if (event.key.code == sf::Keyboard::Escape) {
				game->window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::Q) {
				this->game->changeState(new MainMenu(this->game));
				break;
			}

			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A ||
				event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {
				sf::Keyboard::Key k = event.key.code;
				this->playerMove(k);				
			}				
		}								
		default:
			break;
		}

	}

}

void GameLevel::playerMove(sf::Keyboard::Key& dirKey) {
	sf::Vector2f newPos = player.movePosition(dirKey);
	if (!map.checkCollision(newPos, player)) {
		player.updatePos(newPos);
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

	int mapChoice = rand();


	map = Map("assets/maze.dat", 15,15,32, game->tileAtlas, game, player);

}