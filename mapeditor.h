#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "editor.h"

namespace Log{	
	void MouseTile();
	void MouseCord();
};

using namespace Editor;

class Tile{
public:
	Tile(size_t a, size_t b){
		x = a;
		y = b;
	}
	size_t x;
	size_t y;
	size_t ix; //index x
	size_t iy; //index y
	bool on = false;//tmp
};

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
	std::vector<std::vector<Tile> > blocks;
	bool quit = false;
};