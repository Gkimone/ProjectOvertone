#include "Config.h"
#include "Renderer.h"
#include "Processor.h"
#include "MapHandler.h"
#include "EventHandler.h"

using Overtone::programIsRunning;

int main()
{
	//Init
	InitWorlds();

	//Main Loop
	while (programIsRunning) {
		EventHandler();
		Renderer();
		Processor();
	}

}
