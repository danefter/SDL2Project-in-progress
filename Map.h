#pragma once
#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	void load_map(int array[20][25]);

	void draw_map();

private:

	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};