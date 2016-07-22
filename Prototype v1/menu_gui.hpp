#ifndef MENU_GUI_HPP
#define MENU_GUI_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <map>

#include "game.hpp"


class MenuGui {
public:

	sf::Text menu;
	sf::Font font;

	std::map<std::string, sf::Text> guiText;
	sf::Vector2f guiStart;

	void draw(sf::RenderWindow& window);
	void update(std::string key, std::string newValue);


	MenuGui() {
		font.loadFromFile("assets/Augusta.ttf");

		this->guiText["menu"] = menu;


		guiText["menu"].setString("Press S to Start");
		guiStart.x = 257;
		guiStart.y = 225;

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
};

#endif // !MENU_GUI_HPP