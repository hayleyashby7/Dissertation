#include "gui.hpp"
Gui::Gui() {
	font.loadFromFile("assets/KF.ttf");

	this->guiText["code"] = gameCode;
	this->guiText["level"] = levelNumber;
	this->guiText["key"] = numOfKeys;
	this->guiText["player"] = playerStatus;

	guiText["code"].setString("Code: ");
	guiText["level"].setString("Level: ");
	guiText["key"].setString("Keys Gathered: 0");
	guiText["player"].setString("Health: 100");


	guiStart.x = 557;
	guiStart.y = 25;

	int i = 0;
	for (auto &text : this->guiText) {
		float x = guiStart.x;
		float y = guiStart.y + (i * 100);
		text.second.setPosition(x, y);
		text.second.setFont(font);
		text.second.setColor(sf::Color::White);
		text.second.setCharacterSize(20);
		i++;
	}
};
void Gui::draw(sf::RenderWindow& window) {
	for (auto &text : this->guiText) {
		window.draw(text.second);
	}
}

void Gui::update(std::string key, std::string newValue) {
	guiText[key].setString(newValue);
}