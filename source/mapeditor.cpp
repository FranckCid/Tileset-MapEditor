#include "mapeditor.h"
#include "graphs.h"
#include "log.h"
#include "input.h"
#include "text.h"
#include "debug.h"
#include "editor.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


void MapEditor::init(){
	if(!SDL_Init(SDL_INIT_EVERYTHING)){
		window = SDL_CreateWindow("Map Editor",
								   SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED,
								   Editor::SWIDTH,
								   Editor::SHEIGHT,
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

	Input::handleEvents(event);

	canvas.input(event, tileset);
	tilesetWindow.input(event, tileset);

	quit = Input::quit;
	if(Input::isHolding(SDLK_F3) && !onceDebug){
		debug = !debug;
		onceDebug = true;
	}
	if(!Input::isHolding(SDLK_F3) && onceDebug){
		onceDebug = false;
	}

}

void MapEditor::draw(){
	Graphs::refresh(renderer);
	
	canvas.draw(renderer, tileset);
	tilesetWindow.draw(renderer, tileset);

	if(debug)
		Debug::show(renderer, canvas.transform, tilesetWindow.transform);

	Graphs::apply(renderer);
}

void MapEditor::loop(){
	quit = false;
	debug = false;
	int frames = 0;
	Uint32 startTick = 0;

	while(!quit){
		frames++;
		Uint32 elapsedMS = SDL_GetTicks() - startTick;
		input();
		
		if(elapsedMS){
			double elapsedSeconds = elapsedMS / 1000.0;
			Editor::FPS = frames / elapsedSeconds;
		}

		draw();

		SDL_Delay(1000.0/Editor::MAXFPS);
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
	SDL_Rect r = {Editor::SWIDTH * 0.3, 0, Editor::SWIDTH * 0.7, Editor::SHEIGHT};
	tileset.init(renderer, "textures.png", 16, 16);
	canvas.init(r, tileset);
	r = {0, 0, Editor::SWIDTH * 0.3, Editor::SHEIGHT};
	tilesetWindow.init(r, tileset);
	//Create new doc
}
