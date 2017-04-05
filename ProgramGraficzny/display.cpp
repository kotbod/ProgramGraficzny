#include <iostream>

#include <string>
#include <SDL.h>
#include "display.h"

Display::Display(int width, int height) {
	window = SDL_CreateWindow("Program graficzny", 200, 200, width, height, SDL_WINDOW_MAXIMIZED);
	window_surface = SDL_GetWindowSurface(window);
	
	renderer = SDL_CreateSoftwareRenderer(window_surface);
	SDL_SetRenderDrawColor(renderer, 128,128,128, 255);
	
}

Display::~Display() {
	for (SDL_Surface* texture : texture_pool) {
		SDL_FreeSurface(texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

}

SDL_Renderer* Display::get_renderer() {
	return renderer;
}

SDL_Window* Display::get_window() {
	return window;
}

SDL_Surface* Display::load_texture(std::string path) {
	//SDL_Texture* texture;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == nullptr) {
		std::cout << "Nie mozna otworzyc " << path << std::endl;
		return nullptr;
	}	
	//texture = SDL_CreateTextureFromSurface(renderer, surface);
	//SDL_FreeSurface(surface);
	texture_pool.push_back(surface);
	return surface;
}

void Display::update() {
	SDL_UpdateWindowSurface(window);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

}

