#include <SDL2/SDL.h>
#include "editor.h"

using namespace Editor;

#ifndef GRAPHS
#define GRAPHS
namespace Graphs{

	#ifndef COLOR
	#define COLOR
	namespace Color{
		static const int RED = 0x1;
		static const int GREEN = 0x2;
		static const int GRAY = 0x4;
		static const int WHITE = 0x8;
	}
	#endif

	void refresh(SDL_Renderer *renderer);
	void background(SDL_Renderer *renderer);
	void drawColor(SDL_Renderer *renderer, int color);
	void apply(SDL_Renderer *renderer);

	//Predefined rects
	SDL_Rect rectTile(int x, int y, int w, int h);

	//COLISIONS
	bool inside(int pos, int n1, int nn); //n1 = first pos and nn = last pos
};
#endif