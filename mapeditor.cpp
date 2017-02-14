#include "mapeditor.h"
#include "graphs.h"
#include <SDL/SDL_image.h>

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
				if(IMG_Init(IMG_INIT_PNG)){
					//Set default color
					Graphs::drawColor(renderer, Graphs::Color::GRAY);
					//New doc TODO:: FILE MANAGEMENT
					newDoc();
				}else{
					SDL_Log("Failed to initialize sdl image.");
				}
			}else{
				SDL_Log("Could not create renderer.");
			}
		}else{
			SDL_Log("Could not create window.");
		}
	}else{
		SDL_Log("Could not initialize.");
	}
}

void MapEditor::input(){
	while(SDL_PollEvent(&event)){

		//Get mouse x and y
		SDL_GetMouseState(&mousex, &mousey);
		//Set the horizontal index
		tilex = (size_t) ((mousex / BSIZE) + 0.5);
		//Set the vertical index
		tiley = (size_t) ((mousey / BSIZE) + 0.5);

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
				if(tilex < BWIDTH && tiley << BHEIGHT) // TODO: SAME FOR < 0 when move is aplicated
					blocks[tilex][tiley].on = true;
				break;
			case SDL_MOUSEBUTTONUP:
				
				break;
		}
	}
}

void MapEditor::draw(){
	Graphs::refresh(renderer);
	Graphs::background(renderer);
	//SDL_RenderCopy();
	//Draw Tiles
	for(auto tiles : blocks){
		for(auto tile : tiles){
			SDL_Rect fillRect = Graphs::rectTile(tile.x, tile.y, BSIZE, BSIZE);

			Graphs::drawColor(renderer, Graphs::Color::WHITE);
			if(tile.on){
				Graphs::drawColor(renderer, Graphs::Color::RED);

			}

			bool horizontal = Graphs::inside(mousex, tile.x, BSIZE),
				 vertical = Graphs::inside(mousey, tile.y, BSIZE);
			if(horizontal && vertical){
				Graphs::drawColor(renderer, Graphs::Color::GREEN);
			}

			SDL_RenderFillRect(renderer, &fillRect);
		}
	}
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
	//Create new doc
	for(size_t x=0; x<BWIDTH; x++){
		std::vector<Tile> tVector;
		for(size_t y=0; y<BHEIGHT; y++){
			Tile t(x, y);
			tVector.push_back(t);
		}
		blocks.push_back(tVector);
	}
}

namespace Log{
	void MouseTile(){
		std::cout << "Tile X: " << tilex << std::endl;
		std::cout << "Tile Y: " << tiley << std::endl;
	}

	void MouseCord(){
		std::cout << "Cord X: " << tilex << std::endl;
		std::cout << "Cord Y: " << tiley << std::endl;
	}
}