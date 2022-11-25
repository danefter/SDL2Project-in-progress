#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* texture, int x, int y)
{

	obj_texture = TextureManager::load_texture(texture);
	xpos = x;
	ypos = y;

}

void GameObject::update()
{
	xpos++;
	ypos++;


	src_rect.h = 84;
	src_rect.w = 66;
	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.x = xpos;
	dest_rect.y = ypos;
	dest_rect.w = src_rect.w;
	dest_rect.h = src_rect.h;

}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, obj_texture, &src_rect, &dest_rect);
}


