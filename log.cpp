#include "log.h"
#include "editor.h"
#include <iostream>
#include <SDL2/SDL.h>

using namespace Editor;

namespace Log{

	void info(std::string msg){
		std::cout << msg;
	}

	void infoln(std::string msg){
		std::cout << msg << std::endl;
	}

	void err(std::string msg){
		SDL_Log(msg.c_str());
		SDL_Log(SDL_GetError());
	}

	void MouseTile(){
		std::cout << "Tile X: " << tilex << std::endl;
		std::cout << "Tile Y: " << tiley << std::endl;
	}

	void MouseCord(){
		std::cout << "Cord X: " << mousex << std::endl;
		std::cout << "Cord Y: " << mousey << std::endl;
	}

	void ScreenSize(){
		std::cout << "Width: " << BWIDTH << std::endl;
		std::cout << "Height: " << BHEIGHT << std::endl;
	}

}