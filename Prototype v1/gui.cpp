#include "gui.hpp"

void Gui::draw(sf::RenderWindow& window) {
	for (auto &text : this->guiText) {
		window.draw(text.second);
	}
}

void Gui::update(std::string key, std::string newValue) {
	guiText[key].setString(newValue);
}