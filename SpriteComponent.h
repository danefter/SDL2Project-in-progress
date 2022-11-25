#pragma once

#include "TransformComponent.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect src_rect, dest_rect;

public:
	SpriteComponent() = default;
	//path to texture
	SpriteComponent(const char* path)
	{
		set_texture(path);
	}

	void set_texture(const char* path)
	{
		texture = TextureManager::load_texture(path);
	}

	void init() override
	{
		transform = &entity->get_component<TransformComponent>();
		src_rect.x = src_rect.y = 0;
		src_rect.w = 66;
		src_rect.h = 84;
		dest_rect.w = dest_rect.h = 64;
	}

	void update() override
	{
		dest_rect.x = transform->get_x();
		dest_rect.y = transform->get_y();
	}

	void draw() override
	{
		TextureManager::draw(texture, src_rect, dest_rect);
	}

	 
};