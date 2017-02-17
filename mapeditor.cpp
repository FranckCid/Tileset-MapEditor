#include "mapeditor.h"
#include "graphs.h"
#include "log.h"
#include "input.h"
#include "text.h"
#include "debug.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
				// Images ---------
				int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
				if((IMG_Init(imgFlags)) & imgFlags){
					//Set default color
					Graphs::drawColor(renderer, Graphs::Color::GRAY);
					//New doc TODO:: FILE MANAGEMENT
					newDoc();
					//Init vars TMP
					screenX = 0;
					screenY = 0;
					holdingMiddle = false;	
				}else{
					Log::err("Failed to initialize sdl image.");
				}
				//Text -------
				if( TTF_Init() == -1 ) {
					Log::err("SDL_ttf could not initialize! SDL_ttf Error: ");
				}else{
					Text::loadFont("Ubuntu-L.ttf");
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

	while(SDL_PollEvent(&event)){

		//Handle events
		switch(event.type){
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEWHEEL:
				BSIZE += event.wheel.y;
				/*screenX += event.wheel.x * BSIZE;
				screenY += event.wheel.y * BSIZE;*/ //TODO:: Mouse centered scroll
				if(BSIZE <= 1){
					BSIZE = 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button){
					case SDL_BUTTON_LEFT:
						if(tilex < BWIDTH && tiley < BHEIGHT){ // TODO: SAME FOR < 0 when move is aplicated
							blocks[tilex][tiley].setCord(tileset.getCord(1));
						}
						break;
					case SDL_BUTTON_MIDDLE:
					case SDL_BUTTON_RIGHT:
						//Input::holding(Input::Key::Middle);
						holdingMiddle = true;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				holdingMiddle = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_F3:
						debug = !debug;
						break;
				}
				break;
		}
	}

	//Differente between last mouse pos and actual
	difmousex = mousex - lastmousex;
	difmousey = mousey - lastmousey;

	//Make last mouse position equals actual mouse position
	lastmousex = mousex;
	lastmousey = mousey;

}

void MapEditor::draw(){
	Graphs::refresh(renderer);
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

	if(debug)
		Debug::show(renderer);

	Graphs::apply(renderer);
}

void MapEditor::loop(){

	int frames = 0;
	Uint32 startTick = 0;

	while(!quit){
		frames++;
		Uint32 elapsedMS = SDL_GetTicks() - startTick;
		input();
		
		if(elapsedMS){
			double elapsedSeconds = elapsedMS / 1000.0;
			FPS = frames / elapsedSeconds;
		}

		draw();

		SDL_Delay(1000.0/MAXFPS);
	}
	close();
}

void MapEditor::close(){
	//Todo:: QUIT IMG
	Text::close();
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
