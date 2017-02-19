#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <map>
#include "log.h"

#ifndef TEXT_H
#define TEXT_H
namespace Text{

	extern TTF_Font *font;
	extern std::map<std::string, SDL_Texture*> msgs;

	void loadFont(std::string path, int size=12);

	SDL_Texture* createText(SDL_Renderer*, std::string, int &width, int &height);

	void close();

};
#endif