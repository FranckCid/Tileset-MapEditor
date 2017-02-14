#include "graphs.h"

namespace Graphs{

	void refresh(SDL_Renderer *renderer){
		SDL_RenderClear(renderer);
	}

	void background(SDL_Renderer *renderer){
		drawColor(renderer, Color::GRAY);
		SDL_Rect entireScreen = {0, 0, SWIDTH, SHEIGHT};
		SDL_RenderFillRect(renderer, &entireScreen);
	}

	void drawColor(SDL_Renderer *renderer, int color){
		if(color & Color::WHITE)
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		else if(color & Color::RED){
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
		}else if(color & Color::GREEN){
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x23 );
		}else if(color & Color::GRAY){
			SDL_SetRenderDrawColor(renderer, 0x23, 0x23, 0x23, 0xFF );
		}
	}

	bool inside(int pos, int n1, int nn){ //n1 = first pos and nn = last pos
		return (pos >= n1*nn && pos < n1*nn + nn);
	}

	void apply(SDL_Renderer *renderer){		
		SDL_RenderPresent(renderer);
	}


	SDL_Rect rectTile(int x, int y, int w, int h){
		SDL_Rect r = {x*w, y*h, w, h};
		return r;
	}

}