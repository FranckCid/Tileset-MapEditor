#include "debug.h"
#include "text.h"

namespace Debug{
	void show(SDL_Renderer *renderer){
		int tmpw, tmph;
		SDL_Texture *tmptex = Text::createText(renderer, "Teste mt do loko", tmpw, tmph);
		SDL_Rect tmppos = {0, 0, tmpw, tmph};
		SDL_RenderCopy(renderer, tmptex, NULL, &tmppos);
	}
};