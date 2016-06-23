#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "main_menu_state.hpp"

int main()
{
	Game game;	

	game.changeState(new MainMenu(&game));

	game.gameLoop();	

	return 0;
}
