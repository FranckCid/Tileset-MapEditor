#include "text.h"

namespace Text{

	TTF_Font *font = NULL;
	std::map<std::string, SDL_Texture*> msgs;

	void loadFont(std::string path){
		font = TTF_OpenFont(path.c_str(), 25);
	}

	//TODO add font to a map
	SDL_Texture *createText(SDL_Renderer *renderer, std::string text, int &width, int &height){
		SDL_Texture *texture;

		//Check if there isn't already the same message on the iterator
		auto it = msgs.find(text);
		if(it != msgs.end())
			return it->second;
		
		SDL_Color color = { 255, 255, 255 };
		//Create surface
		SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
		//Return text width and height
		width = surface->w;
		height = surface->h;
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		return texture;
	}

	void close(){
		TTF_CloseFont(font);
		TTF_Quit();
	}

};