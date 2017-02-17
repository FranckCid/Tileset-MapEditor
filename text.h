#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "log.h"

#ifndef TEXT_H
#define TEXT_H
namespace Text{

	extern TTF_Font *font;

	void loadFont(std::string path);

	SDL_Texture* createText(SDL_Renderer*, std::string);

	void close();

};
#endif