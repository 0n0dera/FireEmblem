// FireEmblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main()
{
	Game game;

	game.init();

	game.main_loop();

	game.clean();

    return 0;
}

