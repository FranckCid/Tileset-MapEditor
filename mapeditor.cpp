#include "mapeditor.h"
#include "graphs.h"
#include "log.h"
#include <SDL/SDL_image.h>
#include <iostream>

void MapEditor::init(){
	if(!SDL_Init(SDL_INIT_EVERYTHING)){
		window = SDL_CreateWindow("Map Editor",
								   SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED,
								   SWIDTH,
								   SHEIGHT,
								   SDL_WINDOW_SHOWN);
		if(window){
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer){
				int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
				if((IMG_Init(imgFlags)) & imgFlags){
					//Set default color
					Graphs::drawColor(renderer, Graphs::Color::GRAY);
					//New doc TODO:: FILE MANAGEMENT
					newDoc();					
				}else{
					Log::err("Failed to initialize sdl image.");
				}
			}else{
				Log::err("Could not create renderer.");
			}
		}else{
			Log::err("Could not create window.");
		}
	}else{
		Log::err("Could not initialize.");
	}
}

void MapEditor::input(){

	//Get mouse x and y
	SDL_GetMouseState(&mousex, &mousey);
	//Set the horizontal index
	tilex = (size_t) ((mousex / BSIZE));
	//Set the vertical index
	tiley = (size_t) ((mousey / BSIZE));

	while(SDL_PollEvent(&event)){

		//Handle events
		switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEWHEEL:
				BSIZE += event.wheel.y;
				if(BSIZE <= 1){
					BSIZE = 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(tilex < BWIDTH && tiley < BHEIGHT){ // TODO: SAME FOR < 0 when move is aplicated
					blocks[tilex][tiley].setCord(tileset.getCord(1));
				}
				Log::MouseTile();
				Log::ScreenSize();
				break;
			case SDL_MOUSEBUTTONUP:
				
				break;
		}
	}
}

void MapEditor::draw(){
	Graphs::refresh(renderer);
	Graphs::background(renderer);

	//Draw Tiles
	for(auto tiles : blocks){
		for(auto tile : tiles){

			SDL_Rect c = tile.cord,
					 p = tile.pos();

			bool horizontal = Graphs::inside(mousex, tile.x, BSIZE),
				 vertical = Graphs::inside(mousey, tile.y, BSIZE);
			if(horizontal && vertical){
				c = tileset.getCord(3);
				SDL_RenderCopy(renderer, tile.tex, &c, &p);
				continue;
			}

			if(!tile.empty)
				SDL_RenderCopy(renderer, tile.tex, &c, &p);

		}
	}
	
	Graphs::grid(renderer);

	Graphs::apply(renderer);
}

void MapEditor::loop(){

	while(!quit){
		input();
		draw();	
	}
	close();
}

void MapEditor::close(){
	SDL_Quit();
}

void MapEditor::newDoc(){
	//Todo:: change it to newTileset()
	tileset.init(renderer, "textures.png", 16, 16);
	//Create new doc
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
