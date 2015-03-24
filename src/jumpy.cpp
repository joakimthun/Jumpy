#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>

#include "game.h"


int main( int argc, char* args[] )
{

	auto game = new Game();

	if(game->init())
	{
		game->start();
	}

	delete game;

	return 0;
}

