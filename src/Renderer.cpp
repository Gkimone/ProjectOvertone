#include <windows.h>
#include "ScreenBuilder.h"
#include "MenuBuilder.h"

void Renderer() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	SetConsoleCursorPosition(hOut, coord);
	ScreenBuilder();
	MenuBuilder();
}