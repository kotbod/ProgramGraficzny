#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "GUIelement.h"
#include "pixel.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<typename T> 
class GUI_label: public GUIelement {
private:
	SDL_Surface* surface;
	TTF_Font* font;
	Pixel top_left;
	int text_size;
	T* value;
	T old_value;
public:
	GUI_label(T* value, Pixel top_left, int text_size);
	~GUI_label();

	virtual void update();
	virtual void handle_event(SDL_Event &e);
	virtual void draw(Display* display);
};

template<typename T> 
GUI_label<T>::GUI_label(T* value, Pixel top_left, int text_size) : value(value), top_left(top_left), text_size(text_size) {
	font = TTF_OpenFont("FreeSans.ttf", text_size);
	if (!font) {
		cout << "Nie mozna znalezc czcionki" << endl;
	}
	stringstream text;
	text << *value;
	const SDL_Color BLACK = { 0, 0, 0 };
	surface = TTF_RenderText_Solid(font, text.str().c_str() , BLACK);
}

template<typename T>
GUI_label<T>::~GUI_label() {
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

template<typename T>
void GUI_label<T>::update() {
	if (*value != old_value) {
		old_value = *value;
		stringstream text;
		text << *value;
		const SDL_Color BLACK = { 0, 0, 0 };
		SDL_FreeSurface(surface);
		surface = TTF_RenderText_Solid(font, text.str().c_str(), BLACK);
	}
}

template<typename T>
void GUI_label<T>::handle_event(SDL_Event &e) {

}

template<typename T>
void GUI_label<T>::draw(Display* display) {
	SDL_Rect src = { 0, 0, surface->w, surface->h };
	SDL_Rect dst = { top_left.x, top_left.y, surface->w, surface->h };
	SDL_BlitSurface(surface, &src, display->window_surface, &dst);
}