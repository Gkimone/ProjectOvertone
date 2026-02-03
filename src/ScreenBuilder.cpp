#include "Config.h"

#include "classes/Screen.h"
#include "classes/Entities.h"
#include "classes/Map.h"
#include "classes/Battle.h"

#include "BattleHandler.h"
#include "MapHandler.h"
#include "Player.h"

using Overtone::isTextOnScreen;

void ScreenHandler() {
	if (isTextOnScreen && screen.screenText.isThereText) {
		screen.ScreenTextFiller();
	}
	else if (!screen.screenText.isThereText) {
		isTextOnScreen = false;
		//Negative worlds represent different type of menus
		if (Overtone::cW < 0) {
			switch (Overtone::cW) {
			case -1:
				screen.ScreenFiller(mainMenuScreen);
				break;
			case -3:
				screen.ScreenFiller(bagScreen);
				Overtone::ShowBag();
				screen.ScreenNav();
				break;
			case -4:
				if (battleEngine.thisEnemy != nullptr) {
					screen.ScreenFiller(battleScreen);
					Overtone::ShowBattleStats();
				}
				break;
			case -5:
				screen.ScreenFiller(gameOverScreen);
				break;
			case -6:
				screen.ScreenFiller(finaleScreen);
				break;
				break;
			}
		}
		else {
			MapHandler();
		}
	}
}

void ScreenBuilder() {
	string screenFrame;
	
	ScreenHandler();

	screen.ScreenGen(screenFrame);
}