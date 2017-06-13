#pragma once

#include "surface.h"

void Surface::create() {
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	_surface = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, 0);

	SDL_Rect pixel_rect = { 0, 0, 1, 1 };
	SDL_FillRect(_surface, &pixel_rect, 0x00ff0000);
	if (get_pixel(Pixel(0, 0)) != 0x00ff0000) {
		pixel_format_reversed = true;
		SDL_FreeSurface(_surface);
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		_surface = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, 0);
	}
}

Surface::Surface(int width, int height): width(width), height(height) {
	rect = { 0, 0, width, height };
	create();	
}

Surface::Surface(string pathname) {
	SDL_Surface *loaded = IMG_Load(pathname.c_str());
	if (loaded == nullptr) {
		throw WrongExtension();
	}
	width = loaded->w;
	height = loaded->h;
	rect = { 0, 0, width, height };
	
	create();
	SDL_BlitSurface(loaded, &rect, _surface, &rect);
}

Surface::Surface(Surface &other): Surface(other.width, other.height) {
	blit(&other, &rect);
}

Surface::~Surface() {
	SDL_FreeSurface(_surface);
}

bool Surface::contains(Pixel pos) {

	return pos.x >= 0 && pos.x < _surface->w && pos.y >= 0 && pos.y < _surface->h;
}

bool Surface::contains(SDL_Rect rect) {
	return rect.x >= 0 && rect.y >= 0 && rect.x + rect.w <= _surface->w && rect.y + rect.h <= _surface->h;
}

int Surface::get_pixel(Pixel pos) {
	Uint8 *p = (Uint8 *)_surface->pixels + pos.y * _surface->pitch + pos.x * 3;
	if (pixel_format_reversed) {
		return p[0] << 16 | p[1] << 8 | p[2];
	}
	else {
		return p[2] << 16 | p[1] << 8 | p[0];
	}
}

void Surface::set_pixel(Pixel pos, int colour)
{	
	Uint8 *p = (Uint8 *)_surface->pixels + pos.y * _surface->pitch + pos.x * 3;
	if (pixel_format_reversed) {
		p[0] = colour >> 16;
		p[1] = colour >> 8;
		p[2] = colour >> 0;
	}
	else {
		p[0] = colour >> 0;
		p[1] = colour >> 8;
		p[2] = colour >> 16;
	}
}

void Surface::fill_rectangle(SDL_Rect *rect, int colour) {
	SDL_FillRect(_surface, rect, colour);
}

void Surface::blit(Surface *to_blit, SDL_Rect *rect) {
	SDL_BlitSurface(to_blit->_surface, &to_blit->rect, _surface, rect);
}

Surface *Surface::with_filter(Filter &filter) {
	int border_width = filter.size / 2;
	Surface *new_surf;
	if (filter.include_edges) {
		new_surf = new Surface(width, height);		
	}
	else {
		new_surf = new Surface(width - border_width * 2, height - border_width * 2);
	}
	
	int x_start;
	int y_start;
	int x_limit;
	int y_limit;
	if (filter.include_edges) {
		x_start = 0;
		y_start = 0;
		x_limit = width;
		y_limit = height;
	}
	else {
		x_start = border_width;
		y_start = border_width;
		x_limit = width - border_width;
		y_limit = height - border_width;
	}

	for (int x = x_start; x < x_limit; ++x) {
		for (int y = y_start; y < y_limit; ++y) {
			Pixel p(x, y);
			SDL_Rect kernel_rect = { x - filter.size / 2, y - filter.size / 2, filter.size, filter.size };
			float rsum = 0;
			float gsum = 0;
			float bsum = 0;
			float weight_sum = 0;
			for (int i = 0; i < filter.size; ++i) {
				for (int j = 0; j < filter.size; ++j) {
					Pixel sample_point(kernel_rect.x + i, kernel_rect.y + j);
					float weight;
					if (contains(sample_point)) {
						weight = filter.kernel[j * filter.size + i];
						weight_sum += weight;
						Uint8 r, g, b;
						SDL_GetRGB(get_pixel(sample_point), _surface->format, &r, &g, &b);
						rsum += r * weight;
						gsum += g * weight;
						bsum += b * weight;
					}
				}
			}

			rsum = abs(rsum);
			gsum = abs(gsum);
			bsum = abs(bsum);

			int rnorm;
			int gnorm;
			int bnorm;
			if (weight_sum != 0) {
				rnorm = (int)(rsum / weight_sum);
				gnorm = (int)(gsum / weight_sum);
				bnorm = (int)(bsum / weight_sum);
			}
			else {
				rnorm = (int)rsum;
				gnorm = (int)gsum;
				bnorm = (int)bsum;
			}			 
			int normalized_value = SDL_MapRGB(_surface->format, rnorm, gnorm, bnorm);

			if (filter.include_edges) {
				new_surf->set_pixel(p, normalized_value);
			}
			else {
				new_surf->set_pixel(p - Pixel(border_width, border_width), normalized_value);
			}
			
		}
	}	
	return new_surf;
}

Surface *Surface::as_grayscale() {
	Surface *new_surf = new Surface(width, height);
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			Pixel p(x, y);

			Uint8 r, g, b;
			SDL_GetRGB(get_pixel(p), _surface->format, &r, &g, &b);
			Uint8 grey = (r + g + b) / 3;

			new_surf->set_pixel(p, SDL_MapRGB(_surface->format, grey, grey, grey));
		}
	}

	return new_surf;
}

Surface *Surface::blend(Surface *other, SDL_Rect *dest) {
	Surface *blended = new Surface(*this);
	for (int x = 0; x < dest->w; ++x) {
		for (int y = 0; y < dest->h; ++y) {
			Pixel p1(x + dest->x, y + dest->y);
			Pixel p2(x, y);

			Uint8 intensity1, intensity2;
			// IDK if that is necessary			
			SDL_GetRGB(get_pixel(p1), _surface->format, &intensity1, &intensity1, &intensity1);
			SDL_GetRGB(other->get_pixel(p2), other->_surface->format, &intensity2, &intensity2, &intensity2);
			int int1 = (int)intensity1;
			int int2 = (int)intensity2;
			Uint8 blended_value = (Uint8)(sqrt(int1 * int1 + int2 * int2) / sqrt(2));
			blended->set_pixel(p1, SDL_MapRGB(blended->_surface->format, blended_value, blended_value, blended_value));
		}
	}
	return blended;
}

void Surface::save(string pathname) {
	// Check if the pathname ends with ".bmp"
	if (pathname.find(".bmp") != pathname.length() - 4) {
		pathname += ".bmp";
	}
	SDL_SaveBMP(_surface, pathname.c_str());
}