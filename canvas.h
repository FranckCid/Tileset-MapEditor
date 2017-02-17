#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "editor.h"
#include "tileset.h"
#include "tile.h"

using namespace Editor;

#ifndef CANVAS_H
#define CANVAS_H
class Canvas{
public:
	void init(Tileset &tileset);
	void loop();
	void input(SDL_Event event, Tileset &tileset);
	void draw(SDL_Renderer *renderer, Tileset &tileset);
private:
	std::vector<std::vector<Tile> > blocks;
	bool holdingMiddle;
	int screenX, screenY;
};
#endif