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
		Uint8 r = 0x00, g = 0x00, b = 0x00, a = 0xFF;
		switch(color){
			case Color::WHITE:
				r = 0xFF;
				g = 0xFF;
				b = 0xFF;
			break;
			case Color::RED:
				r = 0xdd;
			break;
			case Color::GREEN:
				g = 0xff;
			break;
			case Color::GRAY:
				r = 0x23;
				g = 0x23;
				b = 0x23;
			break;
			case Color::LIGHTGRAY:
				r = 0x55;
				g = 0x55;
				b = 0x55;
			break;
			case Color::MEDIUMGRAY:
				r = 0x33;
				g = 0x33;
				b = 0x33;
			break;
			case Color::YELLOW:
				r = 0xff;
				g = 0xdf;
			break;
		}
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
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