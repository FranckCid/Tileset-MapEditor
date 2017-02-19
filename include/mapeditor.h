#include <SDL2/SDL.h>
#include "tileset.h"
#include "tilesetwindow.h"
#include "tile.h"
#include "canvas.h"

#ifndef MAPEDITOR_H
#define MAPEDITOR_H
class MapEditor{
public:
	void init();
	void loop();
	void input();
	void draw();
	void close();
private:
	void newDoc();
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	Tileset tileset;
	bool quit, debug;
	bool onceDebug;
	Canvas canvas;
	TilesetWindow tilesetWindow;
};
#endif