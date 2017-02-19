#include "tile.h"
#include "editor.h"

Tile::Tile(int a, int b, SDL_Texture *t){
	x = a;
	y = b;
	tex = t;
	empty = true;
}

SDL_Rect Tile::pos(){
	SDL_Rect r = {x * Editor::BSIZE, y  * Editor::BSIZE, Editor::BSIZE, Editor::BSIZE};
	return r;
}

void Tile::setCord(SDL_Rect c){
	cord = c;
	empty = false;
}