#ifndef GUI_HPP
#define GUI_HPP

#include <SFML\Graphics.hpp>
#include <string>
#include <map>

#include "game.hpp"


class Gui {
public:

	sf::Text playerStatus;
	sf::Text numOfKeys;
	sf::Text levelNumber;
	sf::Text gameCode;
	sf::Font font;

	std::map<std::string, sf::Text> guiText;
	sf::Vector2f guiStart;

	void draw(sf::RenderWindow& window);
	void update(std::string key, std::string newValue);


	Gui() {
		font.loadFromFile("assets/Augusta.ttf");
		this->guiText["player"] = playerStatus;
		this->guiText["key"] = numOfKeys;
		this->guiText["level"] = levelNumber;
		this->guiText["code"] = gameCode;
		
		
		guiStart.x = 525;
		guiStart.y = 25;		

		int i = 1;
		for (auto &text : this->guiText) {
			float x = guiStart.x;
			float y = guiStart.y + (i * 100);			
			text.second.setPosition(x, y);
			text.second.setFont(font);
			text.second.setColor(sf::Color::White);
			text.second.setString("test");
			text.second.setCharacterSize(20);
			i++;
		}
	};	
};

#endif // !GUI_HPP