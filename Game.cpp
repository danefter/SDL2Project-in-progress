#include "Game.h"
#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#include  "ECS.h"
#include  "SpriteComponent.h"
#include  "TransformComponent.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;

Entity::Manager manager;

//create player
auto& player(manager.add_entity());


Game::Game() 
{}

Game::~Game() 
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
				
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		is_running = true;
	}

	
	//brigand = new GameObject("assets/brigandwalkleft1.png", 60, 60);
	map = new Map();

	//gives access to position
	player.add_component<TransformComponent>();
	player.add_component<SpriteComponent>("assets/guywalkright1.png");
}

void Game::handle_events()
{

	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	
	//update entities
	manager.update();
	manager.refresh();

	//check player position
	if(player.get_component<TransformComponent>().get_x() > 100)
	{
		player.get_component<SpriteComponent>().set_texture("assets/brigandwalkleft1.png");
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->draw_map();
	manager.draw();
	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}




