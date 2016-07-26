#include <stack>
#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "game.hpp"
#include "game_state.hpp"



void Game::loadTextures() {
	texmgr.loadTexture("background", "assets/background.png");
	texmgr.loadTexture("floor", "assets/floor.png");
	texmgr.loadTexture("wall", "assets/wall.png");
	texmgr.loadTexture("player", "assets/player.png");
	texmgr.loadTexture("enemy", "assets/enemy.png");
	texmgr.loadTexture("exit", "assets/exit.png");
	texmgr.loadTexture("blockedexit", "assets/blockedExit.png");
	texmgr.loadTexture("start", "assets/start.png");
	texmgr.loadTexture("key", "assets/key.png");
}

void Game::loadTiles() {
	this->tileAtlas["floor"] = Tile(this->tileHeight, texmgr.getRef("floor"), false, Entity::entityType::FLOOR);
	this->tileAtlas["wall"] = Tile(this->tileHeight, texmgr.getRef("wall"), true, Entity::entityType::WALL);
	this->tileAtlas["exit"] = Tile(this->tileHeight, texmgr.getRef("exit"), false, Entity::entityType::EXIT);
	this->tileAtlas["blockedexit"] = Tile(this->tileHeight, texmgr.getRef("blockedexit"), false, Entity::entityType::EXIT);
	this->tileAtlas["start"] = Tile(this->tileHeight, texmgr.getRef("start"), false, Entity::entityType::START);
	this->tileAtlas["key"] = Tile(this->tileHeight, texmgr.getRef("key"), false, Entity::entityType::PICKUP);
}



void Game::pushBackState(GameState* state) {
	states.push_back(state);
	states.back()->init();
}

void Game::popBackState(){
	if (!states.empty()) {
		states.back()->cleanUp();
		states.pop_back();
	}
}

void Game::changeState(GameState* state){
	//if (!states.empty()) {
	//	states.back()->cleanUp();
	//	states.pop_back();
	//}
	states.push_back(state);
	states.back()->init();
}

void Game::goBackState() {
	int penultState = states.size() - 2;
	changeState(states[penultState]);
}

GameState* Game::checkState(){
	if (this->states.empty())
		return nullptr;
	return this->states.back();
}

void Game::draw(const float dt) {
	states.back()->draw(dt);
}

void Game::update(sf::Clock& clock) {
	states.back()->update(clock);
}

void Game::eventHandler() {
	states.back()->eventHandler();
}

void Game::cleanUp() {
	//clean all states
	while (!states.empty()) {
		states.back()->cleanUp();
		states.pop_back();
	}
}

void Game::gameLoop(){
	sf::Clock clock;

	while (this->window.isOpen()) {		
		float dt = clock.getElapsedTime().asSeconds();
		if (checkState() == nullptr)
			continue;
		this->eventHandler();
		this->update(clock);
		this->window.clear(sf::Color::Black);
		this->draw(dt);
		this->window.display();
		if (dt > 0.25f) clock.restart();
	
	}
}

Game::Game(){
	this->loadTextures();
	this->loadTiles();

	this->window.create(sf::VideoMode(750, 550), "Dungeon Game!", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(60);
	this->background.setTexture(this->texmgr.getRef("background"));
	this->bgMusic.openFromFile("assets/sounds/mainmenu.wav");
	this->bgMusic.setVolume(50);
}

Game::~Game(){
	while (!this->states.empty())
		popBackState();
}
