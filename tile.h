#include <SDL2/SDL.h>

#ifndef TILE_H
#define TILE_H
class Tile{
public:
	Tile(int a, int b, SDL_Texture *t);
	SDL_Rect pos();
	void setCord(SDL_Rect c);
	int x;
	int y;
	int ix; //index x
	int iy; //index y
	bool empty;
	SDL_Rect cord;
	SDL_Texture *tex;
};
#endif