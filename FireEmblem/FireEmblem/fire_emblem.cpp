// FireEmblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game.h"

int main()
{
	// initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	Game game;

	if (game.init())
	{
		game.main_loop();
		game.clean();
	}
	
	return 0;
}

