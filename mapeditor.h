#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "editor.h"
#include "tileset.h"
#include "tile.h"
#include "canvas.h"

using namespace Editor;

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
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	Tileset tileset;
	bool quit = false, debug = false;
	Canvas canvas;
};
#endif