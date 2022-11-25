#pragma once
#include "Game.h"

class GameObject
{

public:
	GameObject(const char* texture, int x, int y);
	~GameObject();

	void update();
	void render();

private:

	int xpos;
	int ypos;

	SDL_Texture* obj_texture;
	SDL_Rect src_rect, dest_rect;
	SDL_Renderer* renderer;
};