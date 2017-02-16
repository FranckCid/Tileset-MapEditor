#include <SDL2/SDL.h>
#include <vector>
#include <string>

#ifndef TILESET_H
#define TILESET_H
class Tileset{
public:
	SDL_Texture *texture = NULL;
	std::vector<SDL_Rect> tiles;
	void init(SDL_Renderer *renderer, std::string path, size_t w, size_t h);
	SDL_Rect getCord(int i);
};
#endif