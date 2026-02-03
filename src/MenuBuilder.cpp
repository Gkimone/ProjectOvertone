#include "Config.h"

#include "classes/Menu.h"
#include "classes/Entities.h"
#include "classes/Battle.h"

using Overtone::lW, Overtone::cW, Overtone::cF, Overtone::cZ, Overtone::isTextOnMenu, Overtone::isTextOnScreen, Overtone::isMenuOpen;

char Switch(bool Switch) {
	if (Switch) {
		return 'I';
	}
	else {
		return 'O';
	}
}

void MenuHandler() {
	if (isTextOnMenu && menu.menuText.isThereText) {
		menu.MenuTextFiller();
	}
	else if (!menu.menuText.isThereText) {
		isTextOnMenu = false;
		//Negative worlds represent different type of menus
		switch (cW) {
		case -1:
			isMenuOpen = true;
			menu.MenuFiller(mainMenuOptions);
			break;
		case -2:
			isMenuOpen = true;
			menu.MenuFiller(configMenuOptions);
			menu.MenuCoordFiller(14, 2, Switch(Overtone::sound));
			menu.MenuCoordFiller(14, 4, Switch(Overtone::slowMode));
			break;
		case -3:
			menu.MenuFiller(BagMenuOptions);
			break;
		case -4:
			if (!battleEngine.thisEnemy->alive) {
				menu.MenuFiller(victoryPlaceHolder);
			}
			else if (!battleEngine.enemyTurn) {
				menu.MenuFiller(battleMenuOptions);
			}
			else {
				menu.MenuFiller(enemyTurnPlaceHolder);
			}
			break;
		case -5:
			menu.MenuFiller(gameOverMenu);
			break;
		case -6:
			menu.MenuFiller(creditsMenu);
			break;
		default:
			if (isTextOnScreen) {
				menu.MenuFiller(emptyMenu);
			}
			else {
				menu.MenuFiller(commandMenuOptions);
			}
			
			break;
		}
	}
}

void MenuBuilder() {
	string menuFrame;

	MenuHandler();
	if (isMenuOpen && !isTextOnMenu) {
		menu.MenuNav();
	}

	menu.MenuGen(menuFrame);
}