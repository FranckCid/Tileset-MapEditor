#include "tileset.h"
#include "graphs.h"
#include <iostream>
#include "log.h"

void Tileset::init(SDL_Renderer *renderer, std::string path, size_t w, size_t h){
	texture = Graphs::loadTexture(renderer, path);
	int tWidth, tHeight;
	
	SDL_QueryTexture(texture, NULL, NULL, &tWidth, &tHeight);
	for(int i = 0; i < tWidth; i+=w){
		for(int j = 0; j < tHeight; j+=h){
			SDL_Rect pos = {i, j, w, h};
			tiles.push_back(pos);
		}
	}
}

SDL_Rect Tileset::getCord(int i){
	return tiles[i];
}