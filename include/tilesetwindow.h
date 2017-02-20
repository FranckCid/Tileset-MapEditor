#include <SDL2/SDL.h>
#include <vector>
#include "tileset.h"
#include "tile.h"
#include "panel.h"

#ifndef TILESET_WINDOW_H
#define TILESET_WINDOW_H
class TilesetWindow : public Panel{
public:
	TilesetWindow();
	void init(SDL_Rect screenPos, Tileset &tileset);
	void input(SDL_Event &event, Tileset &tileset);
	void draw(SDL_Renderer *renderer, Tileset &tileset);
private:
	std::vector<std::vector<Tile> > blocks;
};
#endif