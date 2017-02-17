#include "input.h"
#include <iostream>

/* PRESS IS FOR MOUSE
   HOLDING IS FOR KEYS */

namespace Input{
	std::map<Uint8, bool> keyMap;
	std::map<Uint8, bool> mouseMap;
	bool quit = false;
	int wheelx=0, wheely=0;

	void handleEvents(SDL_Event &evnt){
		
		wheelx = 0;
		wheely = 0;

		while(SDL_PollEvent(&evnt)){
			//Handle events
			switch(evnt.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					holding(evnt.key.keysym.sym);
					break;
				case SDL_KEYUP:
					notHolding(evnt.key.keysym.sym);
					break;
				case SDL_MOUSEWHEEL:
					wheelx = evnt.wheel.x;
					wheely = evnt.wheel.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(evnt.button.button){
						case SDL_BUTTON_LEFT:
							holding(SDL_BUTTON_LEFT);
							break;
						case SDL_BUTTON_MIDDLE:
							holding(SDL_BUTTON_MIDDLE);
							break;
						case SDL_BUTTON_RIGHT:
							holding(SDL_BUTTON_RIGHT);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(evnt.button.button){
						case SDL_BUTTON_LEFT:
							notHolding(SDL_BUTTON_LEFT);
							break;
						case SDL_BUTTON_MIDDLE:
							notHolding(SDL_BUTTON_MIDDLE);
							break;
						case SDL_BUTTON_RIGHT:
							notHolding(SDL_BUTTON_RIGHT);
							break;
					}
					break;
			}
		}
	}

	void holding(Uint8 key){
		auto it = keyMap.find(key); //iterator
		if(it != keyMap.end()){
			it->second = true;
		}else{
			keyMap.insert(std::pair<Uint8, bool>(key, true));
		}
	}

	void notHolding(Uint8 key){
		auto it = keyMap.find(key); //iterator
		if(it != keyMap.end()){
			it->second = false;
		}else{
			keyMap.insert(std::pair<Uint8, bool>(key, false));
		}
		std::cout << ((it->second) ? "true" : "false") << std::endl;
	}

	bool isHolding(Uint8 key){
		auto it = keyMap.find(key); //iterator
		if(it != keyMap.end()){
			return it->second;
		}
	}

};