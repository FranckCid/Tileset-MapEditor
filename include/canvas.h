#include <SDL2/SDL.h>
#include <vector>
#include "tileset.h"
#include "tile.h"

#ifndef CANVAS_H
#define CANVAS_H
class Canvas{
public:
	void init(Tileset &tileset);
	void loop();
	void input(SDL_Event &event, Tileset &tileset);
	void draw(SDL_Renderer *renderer, Tileset &tileset);
private:
	std::vector<std::vector<Tile> > blocks;
	bool holdingMiddle;
	int screenX, screenY;
};
#endif