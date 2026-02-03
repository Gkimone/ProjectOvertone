#include "Config.h"
#include "Renderer.h"
#include "Processor.h"
#include "MapHandler.h"
#include "EventHandler.h"
#include "AIConsoleControl.h"

using Overtone::programIsRunning;

int main()
{
	//Init
	InitWorlds();
	SetupConsoleWindow();

	//Main Loop
	while (programIsRunning) {
		EventHandler();
		Renderer();
		Processor();
	}
}