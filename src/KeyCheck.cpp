#include <conio.h>
#include <iostream>

#include "KeyCheck.h"
#include "Config.h"

#include "classes/Entities.h"
#include "classes/Screen.h"
#include "classes/Menu.h"
#include "classes/Battle.h"

bool TextCheck() {
	if (Overtone::isTextOnMenu || Overtone::isTextOnScreen) return true;
	else return false;
}

void Debug() {
	std::cout << MC.pos.X << std::endl;
	std::cout << MC.pos.Y << std::endl;
	std::cout << MC.thisInteractive.tilePos.X << std::endl;
	std::cout << MC.thisInteractive.tilePos.Y << std::endl;
	std::cout << MC.oldPos.X << std::endl;
	std::cout << MC.oldPos.Y << std::endl;
	std::cout << MC.lastTile << std::endl;
	std::cout << MC.currentTile << std::endl;
	std::cout << MC.nextTile << std::endl;
	std::cout << MC.canInteract << std::endl;
	std::cout << MC.currentWorldInt.size() << std::endl;
	if (MC.inBattle) {
		std::cout << battleEngine.thisEnemy->stats.hp << std::endl;
		std::cout << battleEngine.thisEnemy->stats.atk << std::endl;
		std::cout << battleEngine.thisEnemy->stats.cri << std::endl;
	}
}

void CommandHelper() {
	if (TextCheck()) {
		std::cout << "< Continue >";
	} 
	else if (MC.canInteract) {
		std::cout << "< Interact >";
	}
	else {
		std::cout << "                                  ";
	}
}

void KeyCheck() {
	//Debug();
	CommandHelper();
	int specialKey = 0, key = _getch();
	if (key == 0 || key == 224) {
		specialKey = _getch();
	}
	if (MC.alive) {
		if (!TextCheck()) {
			if (key == 27) {
				Overtone::programIsRunning = false;
			}
			else if (Overtone::isMenuOpen) {
				if (MC.inBattle) {
					battleEngine.BattleKeyChecks(key, specialKey);
				}
				else {
					menu.MenuKeyChecks(key, specialKey);
				}
			}
			else if (Overtone::cW < 0) {
				screen.ScreenKeyChecks(key, specialKey, MC.bag, MC.stats);
			}
			else if (Overtone::cW >= 0) {
				MC.KeyChecks(key, specialKey, screen);
			}
		}
	}
}