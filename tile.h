#include <SDL2/SDL.h>
#include "editor.h"

using namespace Editor;

#ifndef TILE_H
#define TILE_H
class Tile{
public:
	Tile(size_t a, size_t b, SDL_Texture *t){
		x = a;
		y = b;
		tex = t;
		empty = true;
	}
	SDL_Rect pos(){
		SDL_Rect r = {x * BSIZE, y  * BSIZE, BSIZE, BSIZE};
		return r;
	}
	void setCord(SDL_Rect c){
		cord = c;
		empty = false;
	}
	size_t x;
	size_t y;
	size_t ix; //index x
	size_t iy; //index y
	bool empty;
	SDL_Rect cord;
	SDL_Texture *tex;
};
#endif