#include "graphs.h"
#include "log.h"
#include "editor.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace Graphs{

	std::map<std::string, SDL_Texture*> textures;

	void refresh(SDL_Renderer *renderer){
		SDL_RenderClear(renderer);
	}

	void background(SDL_Renderer *renderer){
		drawColor(renderer, Color::GRAY);
		SDL_Rect entireScreen = {0, 0, Editor::SWIDTH, Editor::SHEIGHT};
		SDL_RenderFillRect(renderer, &entireScreen);
	}

	void drawColor(SDL_Renderer *renderer, int color){
		if(color & Color::WHITE)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		else if(color & Color::RED){
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
		}else if(color & Color::GREEN){
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF );
		}else if(color & Color::GRAY){
			SDL_SetRenderDrawColor(renderer, 0x23, 0x23, 0x23, 0xFF );
		}else if(color & Color::LIGHTGRAY){
			SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xFF );
		}else if(color & Color::MEDIUMGRAY){
			SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF );
		}
	}

	bool inside(int pos, int n1, int nn){ //n1 = first pos and nn = last pos
		return (pos >= n1*nn && pos < n1*nn + nn);
	}

	bool insideBox(int x, int y, SDL_Rect &pos){
		bool hor = (Editor::mousex >= pos.x && Editor::mousex <= pos.x + pos.w);
		bool ver = (Editor::mousey >= pos.y && Editor::mousey <= pos.y + pos.h);
		return (hor && ver);
	}

	void apply(SDL_Renderer *renderer){		
		SDL_RenderPresent(renderer);
	}

	SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string path){
		return loadTexture(renderer, path.c_str());
	}

	SDL_Texture *loadTexture(SDL_Renderer *renderer, const char* path){
		SDL_Texture *tex = NULL;
		auto it = textures.find(std::string(path)); //iterator
		if(it != textures.end()){
			return it->second;
		}else{
			SDL_Surface *surface = IMG_Load(path);
			
			if(surface){
				tex = SDL_CreateTextureFromSurface(renderer, surface);
				if(tex){
					
					if(tex){
						
					}
				}else{				
					Log::err("Could not create texture.");
				}
				SDL_FreeSurface(surface);
			}else{
				Log::err("Could not load surface.");
			}
			textures.insert(std::pair<std::string, SDL_Texture*>(std::string(path), tex));
		}
		return tex;
	}

	SDL_Texture *randTexture(){
		auto it = textures.begin();
		std::advance(it, rand() % textures.size());
		SDL_Texture *t = it->second;
		return t;
	}

	SDL_Rect rectTile(int x, int y, int w, int h){
		SDL_Rect r = {x*w, y*h, w, h};
		return r;
	}

	void grid(SDL_Renderer *renderer, int sx, int sy){
		drawColor(renderer, Color::LIGHTGRAY);
		for(int x=0; x < Editor::BWIDTH*Editor::BSIZE+1; x += Editor::BSIZE){
			SDL_RenderDrawLine(renderer, x + sx, 0 + sy, x + sx, Editor::BHEIGHT * Editor::BSIZE + sy);
		}
		for(int y=0; y < Editor::BHEIGHT*Editor::BSIZE+1; y += Editor::BSIZE){
			SDL_RenderDrawLine(renderer, 0 + sx, y + sy, Editor::BWIDTH * Editor::BSIZE + sx, y + sy);
		}
		drawColor(renderer, Color::GRAY);
	}

}