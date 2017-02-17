#include "debug.h"
#include "text.h"
#include "editor.h"
#include "graphs.h"
#include <sstream>

using namespace Editor;

namespace Debug{
	void show(SDL_Renderer *renderer){
		int tmpw, tmph;
		SDL_Rect tmppos;
		SDL_Texture *tmptex = NULL;
		const int length = 3;
		std::ostringstream strs[length];

		//Statistics
		strs[0] << "FPS: " << (int)FPS << "/" << (int)MAXFPS;
		strs[1] << "Tile: " << tilex << "/" << tiley;
		strs[2] << "Mouse: " << mousex << "/" << mousey;
		for(int i=0; i < length; i++){
			tmptex = Text::createText(renderer, strs[i].str().c_str(), tmpw, tmph);
			tmppos = {0, SHEIGHT-(12*(i+1)), tmpw, tmph};
			SDL_RenderCopy(renderer, tmptex, NULL, &tmppos);
		}

		//Mouse grid
		Graphs::drawColor(renderer, Graphs::Color::LIGHTGRAY);
		SDL_RenderDrawLine(renderer, mousex, 0, mousex, mousey);
		SDL_RenderDrawLine(renderer, 0, mousey, mousex, mousey);
		std::ostringstream str; str << "x:" << mousex << ", " << "y:" << mousey;
		tmptex = Text::createText(renderer, str.str(), tmpw, tmph);
		tmppos = {mousex + 10, mousey + 15, tmpw, tmph};
		SDL_RenderCopy(renderer, tmptex, NULL, &tmppos);
	}
};