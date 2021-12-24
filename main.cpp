
// 2D Platformer using c++ 
// using olcPixelGameEngine by Javidx9 - OneLoneCoder

#include "RPG_Engine.h"

int main()
{
	RPG_Engine game;
	if (game.ConstructConsole(260, 240, 4, 4))
		game.Start();

	return 0;
}

