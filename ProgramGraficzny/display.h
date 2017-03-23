#pragma once

#include <vector>

#include <string>
#include <SDL.h>


class Display {
public:
	SDL_Surface* window_surface;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_Texture*> texture_pool;
public:
	Display(int width, int height);
	~Display();

	SDL_Renderer* get_renderer();
	SDL_Window* get_window();

	SDL_Texture* load_texture(std::string path);
	void update();
};
