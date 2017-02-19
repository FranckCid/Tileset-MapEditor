#include "mapeditor.h"
#include "graphs.h"
#include "log.h"
#include "input.h"
#include "debug.h"
#include "editor.h"
#include <iostream>

void Canvas::init(Tileset &tileset){
	screenX = 0;
	screenY = 0;
	holdingMiddle = false;
	for(size_t x=0; x<Editor::BWIDTH; x++){
		std::vector<Tile> tVector;
		for(size_t y=0; y<Editor::BHEIGHT; y++){
			Tile t(x, y, tileset.texture);
			tVector.push_back(t);
		}
		blocks.push_back(tVector);
	}
}

void Canvas::input(SDL_Event &event, Tileset &tileset){
	//Get the actual mouse x and y
	SDL_GetMouseState(&Editor::mousex, &Editor::mousey);
	//Set the horizontal index
	Editor::tilex = ((Editor::mousex - screenX) / Editor::BSIZE);
	//Set the vertical index
	Editor::tiley = ((Editor::mousey - screenY) / Editor::BSIZE);
	//Check middle mouse and move
	if(holdingMiddle){
		// Move screen relative to scroll
		screenX += Editor::difmousex;
		screenY += Editor::difmousey;
	}

	//TODO:: INPUT NAMESPACE
	Editor::BSIZE += Input::wheely;
	if(Editor::BSIZE <= 1){
		Editor::BSIZE = 1;
	}

	if(Input::isHolding(SDL_BUTTON_LEFT)){
		if(Editor::tilex < Editor::BWIDTH && Editor::tiley < Editor::BHEIGHT && Editor::tilex >= 0 && Editor::tiley >= 0){ // TODO: SAME FOR < 0 when move is aplicated
			blocks[Editor::tilex][Editor::tiley].setCord(tileset.actualTile->cord);
		}
	}else if(Input::isHolding(SDL_BUTTON_MIDDLE) || Input::isHolding(SDL_BUTTON_RIGHT)){
		holdingMiddle = true;
	}

	if(!Input::isHolding(SDL_BUTTON_MIDDLE) && !Input::isHolding(SDL_BUTTON_RIGHT)){
		holdingMiddle = false;
	}

	
	//Differente between last mouse pos and actual
	Editor::difmousex = Editor::mousex - Editor::lastmousex;
	Editor::difmousey = Editor::mousey - Editor::lastmousey;

	//Make last mouse position equals actual mouse position
	Editor::lastmousex = Editor::mousex;
	Editor::lastmousey = Editor::mousey;
}

void Canvas::draw(SDL_Renderer *renderer, Tileset &tileset){
	Graphs::background(renderer);
	Graphs::drawColor(renderer, Graphs::Color::MEDIUMGRAY);
	SDL_Rect imgBackRect = {0 + screenX, 0 + screenY, Editor::BWIDTH * Editor::BSIZE, Editor::BHEIGHT * Editor::BSIZE};
	SDL_RenderFillRect(renderer, &imgBackRect);
	Graphs::drawColor(renderer, Graphs::Color::GRAY);

	//Draw Tiles
	for(auto tiles : blocks){
		for(auto tile : tiles){

			SDL_Rect c = tile.cord,
					 p = tile.pos();

			p.x += screenX;
			p.y += screenY;

			if(tile.x == Editor::tilex && tile.y == Editor::tiley){
				SDL_RenderCopy(renderer, tileset.actualTile->tex, &tileset.actualTile->cord, &p);
			}

			if(!tile.empty){
				SDL_RenderCopy(renderer, tile.tex, &c, &p);
			}

		}
	}
	
	Graphs::grid(renderer, screenX, screenY);
}