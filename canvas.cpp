#include "mapeditor.h"
#include "graphs.h"
#include "log.h"
#include "input.h"
#include "debug.h"
#include <iostream>

void Canvas::init(Tileset &tileset){
	screenX = 0;
	screenY = 0;
	holdingMiddle = false;
	for(size_t x=0; x<BWIDTH; x++){
		std::vector<Tile> tVector;
		for(size_t y=0; y<BHEIGHT; y++){
			Tile t(x, y, tileset.texture);
			//t.setCord(tileset.getCord(43));
			tVector.push_back(t);
		}
		blocks.push_back(tVector);
	}
}

void Canvas::input(SDL_Event event, Tileset &tileset){
	//Get the actual mouse x and y
	SDL_GetMouseState(&mousex, &mousey);
	//Set the horizontal index
	tilex = ((mousex - screenX) / BSIZE);
	//Set the vertical index
	tiley = ((mousey - screenY) / BSIZE);
	//Check middle mouse and move
	if(holdingMiddle){
		// Move screen relative to scroll
		screenX += difmousex;
		screenY += difmousey;
	}

	//TODO:: INPUT NAMESPACE
	BSIZE += Input::wheely;
	if(BSIZE <= 1)
		BSIZE = 1;

	if(Input::isHolding(SDL_BUTTON_LEFT)){
		if(tilex < BWIDTH && tiley < BHEIGHT){ // TODO: SAME FOR < 0 when move is aplicated
			blocks[tilex][tiley].setCord(tileset.getCord(1));
		}
	}else if(Input::isHolding(SDL_BUTTON_MIDDLE) || Input::isHolding(SDL_BUTTON_RIGHT)){
		holdingMiddle = true;
	}

	if(!Input::isHolding(SDL_BUTTON_MIDDLE) && !Input::isHolding(SDL_BUTTON_RIGHT)){
		holdingMiddle = false;
	}
}

void Canvas::draw(SDL_Renderer *renderer, Tileset &tileset){
	Graphs::background(renderer);
	Graphs::drawColor(renderer, Graphs::Color::MEDIUMGRAY);
	SDL_Rect imgBackRect = {0 + screenX, 0 + screenY, BWIDTH * BSIZE, BHEIGHT * BSIZE};
	SDL_RenderFillRect(renderer, &imgBackRect);
	Graphs::drawColor(renderer, Graphs::Color::GRAY);

	//Draw Tiles
	for(auto tiles : blocks){
		for(auto tile : tiles){

			SDL_Rect c = tile.cord,
					 p = tile.pos();

			p.x += screenX;
			p.y += screenY;

			if(tile.x == tilex && tile.y == tiley){
				c = tileset.getCord(3);
				SDL_RenderCopy(renderer, tile.tex, &c, &p);
			}

			if(!tile.empty)
				SDL_RenderCopy(renderer, tile.tex, &c, &p);


		}
	}
	
	Graphs::grid(renderer, screenX, screenY);
}

void Canvas::loop(){

}