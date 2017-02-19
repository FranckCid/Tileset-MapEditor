#include <SDL2/SDL.h>
#include <iostream>
#include "mapeditor.h"

int main(int argv, char* args[]){

	srand(time(0));

	MapEditor editor;

	editor.init();
	editor.loop();

	return 0;
}