#include "tilesetwindow.h"
#include "graphs.h"
#include "tile.h"
#include "input.h"
#include "editor.h"
#include <iostream>

void TilesetWindow::init(Tileset &tileset){}

void TilesetWindow::draw(SDL_Renderer *renderer, Tileset &tileset){
	Graphs::drawColor(renderer, Graphs::Color::MEDIUMGRAY);
	SDL_Rect r = {0, 0, 200, Editor::SHEIGHT};
	SDL_RenderFillRect(renderer, &r);

	int x=0, y=0; //200 is the container size, 16 is the tile witdth, change both later
	for(int i=0; i<tileset.tiles.size();){
		int w = tileset.tiles[i].cord.w;
		int h = tileset.tiles[i].cord.h;
		for(;x<200/16; x++){
			SDL_Rect pos = {x*w, y*h, w, h};
			if(!Graphs::insideBox(Editor::mousex, Editor::mousey, pos)){
				SDL_RenderCopy(renderer, tileset.texture, &(tileset.tiles[i].cord), &pos);
			}else{
				if(Input::isHolding(SDL_BUTTON_LEFT)){
					tileset.actualTile = &(tileset.tiles[i]);
				}
			}
			i++;
		}
		x=0;
		y++;
	}

}

void TilesetWindow::input(SDL_Event &event, Tileset &tileset){

}