#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game.hpp"
#include "main_menu_state.hpp"

int main(int argc , char *argv[])
{
	Game game;	

	game.changeState(new MainMenu(&game));

	game.gameLoop();	

	return 0;
}
