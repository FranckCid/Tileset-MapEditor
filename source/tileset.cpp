#include "tileset.h"
#include "graphs.h"
#include <iostream>
#include "log.h"

void Tileset::init(SDL_Renderer *renderer, std::string path, int w, int h){
	texture = Graphs::loadTexture(renderer, path);
	int tWidth, tHeight;
	
	SDL_QueryTexture(texture, NULL, NULL, &tWidth, &tHeight);
	for(int i = 0; i < tWidth; i+=w){
		for(int j = 0; j < tHeight; j+=h){
			Tile t(1,1, texture);
			SDL_Rect pos = {i, j, w, h};
			t.setCord(pos);
			tiles.push_back(t);
		}
	}
	actualTile = &tiles[0];
}

SDL_Rect Tileset::getCord(int i){
	return tiles[i].cord;
}