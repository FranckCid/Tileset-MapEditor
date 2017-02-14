#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "mapeditor.h"

int main(int argv, char* args[]){

	MapEditor editor;

	editor.init();
	editor.loop();

	return 0;
}