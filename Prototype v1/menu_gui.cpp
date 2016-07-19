#include "menu_gui.hpp"

void MenuGui::draw(sf::RenderWindow& window) {
	for (auto &text : this->guiText) {
		window.draw(text.second);
	}
}

void MenuGui::update(std::string key, std::string newValue) {
	guiText[key].setString(newValue);
}