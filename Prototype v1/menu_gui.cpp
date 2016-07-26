#include "menu_gui.hpp"

void MenuGui::init(int height, int width) {
	font.loadFromFile("assets/KF.ttf");
	start.setString("Start");
	info.setString("How to Play");
	credits.setString("Credits");

	
	this->menuText.push_back(start);
	this->menuText.push_back(info);
	this->menuText.push_back(credits);
	int i = 1;
	for (auto &text : this->menuText) {
		text.setPosition(sf::Vector2f(width / 3, ((height / (menuText.size() + 1) * i))));
		text.setFont(font);
		text.setColor(sf::Color::White);
		text.setCharacterSize(30);
		i++;
	}
	this->selectedOption = 0;
	menuText[selectedOption].setColor(sf::Color::Red);
	menuText[selectedOption].setCharacterSize(40);
};

void MenuGui::draw(sf::RenderWindow& window) {
	for (auto &text : this->menuText) {
			window.draw(text);
	}	
}

void MenuGui::MoveUp() {
	if (selectedOption - 1 >= 0) {
		menuText[selectedOption].setColor(sf::Color::White);
		menuText[selectedOption].setCharacterSize(30);
		selectedOption--;
		menuText[selectedOption].setColor(sf::Color::Red);
		menuText[selectedOption].setCharacterSize(40);
	}
}
void MenuGui::MoveDown() {
	if (selectedOption + 1 < menuText.size()) {
		menuText[selectedOption].setColor(sf::Color::White);
		menuText[selectedOption].setCharacterSize(30);
		selectedOption++;
		menuText[selectedOption].setColor(sf::Color::Red);
		menuText[selectedOption].setCharacterSize(40);
	}
}
int MenuGui::getSelection() {
	return this->selectedOption;
}