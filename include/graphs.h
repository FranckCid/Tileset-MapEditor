#include <SDL2/SDL.h>
#include <string>
#include <map>

#ifndef GRAPHS
#define GRAPHS
namespace Graphs{

	namespace Color{
		static const int RED = 1;
		static const int GREEN = 2;
		static const int GRAY = 4;
		static const int WHITE = 8;
		static const int LIGHTGRAY = 16;
		static const int MEDIUMGRAY = 32;
		static const int YELLOW = 64;
	}
	
	//Textures map, i made it so it never repeats
	extern std::map<std::string, SDL_Texture*> textures;

	void refresh(SDL_Renderer *renderer);
	void background(SDL_Renderer *renderer);
	void drawColor(SDL_Renderer *renderer, int color);
	void apply(SDL_Renderer *renderer);

	//Draw
	void grid(SDL_Renderer*, int sx, int sy);

	//Loads
	SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string path);
	SDL_Texture *loadTexture(SDL_Renderer *renderer, const char* path);

	//Predefined
	SDL_Rect rectTile(int x, int y, int w, int h);

	//Random
	SDL_Texture *randTexture(); //TODO: make it REALLY random

	//COLISIONS
	bool inside(int pos, int n1, int nn); //n1 = first pos and nn = last pos
	bool insideBox(int x, int y, SDL_Rect &pos);
};
#endif