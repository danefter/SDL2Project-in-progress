#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handle_events();
	void update();
	void render();
	void clean();
	bool running() { return is_running; }

	static SDL_Renderer* renderer;

private:
	int cnt =0;
	bool is_running = false;;
	SDL_Window* window;

};


#endif