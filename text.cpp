#include "text.h"

namespace Text{

	TTF_Font *font = NULL;

	void loadFont(std::string path){
		font = TTF_OpenFont(path.c_str(), 25);
	}

	SDL_Texture *createText(SDL_Renderer *renderer, std::string text){
		SDL_Color color = { 255, 255, 255 };
		SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		return texture;
	}

	void close(){
		TTF_CloseFont(font);
	}

};