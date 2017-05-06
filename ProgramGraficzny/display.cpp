#include <iostream>

#include <string>
#include <SDL.h>
#include "display.h"
#include <SDL_image.h>

Display::Display(int width, int height) : Display(width, height, true) {}

Display::Display(int width, int height, bool fullscreen) {
	SDL_WindowFlags window_flag;
	window_flag = fullscreen ? SDL_WINDOW_MAXIMIZED : SDL_WINDOW_SHOWN;
	window = SDL_CreateWindow("Program graficzny", 200, 200, width, height, window_flag);
	window_surface = SDL_GetWindowSurface(window);
	
	renderer = SDL_CreateSoftwareRenderer(window_surface);
	SDL_SetRenderDrawColor(renderer, 128,128,128, 255);
	
}

Display::~Display() {
	for (SDL_Surface* texture : texture_pool) {
		SDL_FreeSurface(texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(window_surface);
	SDL_DestroyWindow(window);	
}

SDL_Renderer* Display::get_renderer() {
	return renderer;
}

SDL_Window* Display::get_window() {
	return window;
}

SDL_Surface* Display::load_texture(std::string path) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		std::cout << "Nie mozna otworzyc " << path << std::endl;
		return nullptr;
	}	
	texture_pool.push_back(surface);
	return surface;
}

void Display::update() {
	SDL_UpdateWindowSurface(window);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

