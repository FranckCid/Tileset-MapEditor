#include <SDL2/SDL.h>
#include <iostream>

bool init();
bool loadMedia();
void close();

const size_t SCREEN_WIDTH = 680, SCREEN_HEIGHT = 460;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *helloWorld = NULL;

bool quit = false;
SDL_Event evnt;

int main(int argv, char** args){
	if(!init()){
		std::cout << "Failed to initialize";
	}else{
		if(!loadMedia()){
			std::cout << "Coudn't load resource";
		}else{
			while(!quit){
				SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
				SDL_UpdateWindowSurface(window);
				while(SDL_PollEvent(&evnt)){
				
					if(evnt.type == SDL_QUIT){
						quit = true;
						break;
					}
				
				}
			}
		}
	}
	close();
	return 0;
}

bool init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cout << "Could not initialize." << std::endl;
		return false;
	}else{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL){
			std::cout << "Failed to create window" << std::endl;
			return false;
		}else{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return true;
}

bool loadMedia(){
	helloWorld = SDL_LoadBMP("preview.bmp");
	if(helloWorld == NULL){
		std::cout << "Failed to load resource" << std::endl;
		return false;
	}
	return true;
}

void close(){
	SDL_FreeSurface(helloWorld);
	helloWorld = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}