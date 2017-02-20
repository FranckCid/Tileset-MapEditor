#include <SDL2/SDL.h>
#include <vector>
#include "tileset.h"
#include "tile.h"
#include "panel.h"

#ifndef CANVAS_H
#define CANVAS_H
class Canvas : public Panel{
public:
	Canvas();
	void init(SDL_Rect screenPos, Tileset &tileset);
	void loop();
	void input(SDL_Event &event, Tileset &tileset);
	void draw(SDL_Renderer *renderer, Tileset &tileset);
private:
	std::vector<std::vector<Tile> > blocks;
	bool holdingMiddle;
	int screenX, screenY;
};
#endif