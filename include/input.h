#include <map>
#include <SDL2/SDL.h>

namespace Input{
	extern std::map<Uint8, bool> keyMap;
	extern std::map<Uint8, bool> mouseMap;
	extern bool quit;
	extern int wheelx, wheely;

	void handleEvents(SDL_Event &event);
	void holding(Uint8 key);
	void notHolding(Uint8 key);
	bool isHolding(Uint8 key);
	void pressing(Uint8 key);
	void notPressing(Uint8 key);
	bool isPressing(Uint8 key);
};