#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "tile.h"

#ifndef TILESET_H
#define TILESET_H
class Tileset{
public:
	SDL_Texture *texture = NULL;
	std::vector<Tile> tiles;
	void init(SDL_Renderer *renderer, std::string path, int w, int h);
	SDL_Rect getCord(int i);
	Tile *actualTile;
};
#endif