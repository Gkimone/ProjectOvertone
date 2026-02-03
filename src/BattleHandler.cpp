#include "Config.h"

#include "utils/ArrayHandler.h"

#include "classes/Battle.h"
#include "classes/Entities.h"

#include "Player.h"
#include "EntityHandler.h"

namespace Overtone {

	void StatWritter(int XposMin, int XposMax, int Ypos, int num) {
		int c = 1;
		for (int i = XposMin; i <= XposMax; i++) {
			screen.ScreenCoordFiller(i, Ypos, Utils::IntToCharLength4(num, c));
			c++;
		}
	}
	void StatWritter2(int XposMin, int XposMax, int Ypos, int num) {
		int c = 1;
		for (int i = XposMin; i <= XposMax; i++) {
			screen.ScreenCoordFiller(i, Ypos, Utils::IntToCharLength2(num, c));
			c++;
		}
	}

	void ShowBattleStats() {
		//HP
		StatWritter(7, 10, 1, battleEngine.thisEnemy->stats.hp);
		StatWritter(7, 10, 16, MC.stats.hp);
		//MEDS
		StatWritter2(3, 4, 16, MC.bag.med);
		//AMMO
		StatWritter2(15, 16, 16, MC.bag.amm);
	}

	void BattleEncounter() {
		if (!MC.inBattle) {
			battleEngine.thisEnemy = nullptr;
			bool canBattle;
			for (int i = 1; i <= enemyTypes; i++) {
				char thisEnemy = EntityGlyphChecker(i);
				if (screen.screen[MC.pos.Y + 1][MC.pos.X] == thisEnemy) {
					MC.thisInteractive.tilePos = { MC.pos.X, MC.pos.Y + 1 };
					canBattle = true;
				}
				else if (screen.screen[MC.pos.Y - 1][MC.pos.X] == thisEnemy) {
					MC.thisInteractive.tilePos = { MC.pos.X, MC.pos.Y - 1 };
					canBattle = true;
				}
				else if (screen.screen[MC.pos.Y][MC.pos.X + 1] == thisEnemy) {
					MC.thisInteractive.tilePos = { MC.pos.X + 1, MC.pos.Y };
					canBattle = true;
				}
				else if (screen.screen[MC.pos.Y][MC.pos.X - 1] == thisEnemy) {
					MC.thisInteractive.tilePos = { MC.pos.X - 1, MC.pos.Y };
					canBattle = true;
				}
				else canBattle = false;

				if (canBattle) {
					MC.inBattle = true;
					isMenuOpen = true;
					battleEngine.enemyTurn = false;
					battleEngine.playerTurn = false;
					lW = cW;
					cW = -4;
					switch (thisEnemy) {
					case 's':
						menu.MenuTextBufferFiller(safeEnemyTitle, safeEnemyDialogue);
						Safe.StatRandomizer(50, 100, 5, 10, 0.01f, 0.05f);
						battleEngine.EnemyFiller(&Safe);
						break;
					case 'e':
						menu.MenuTextBufferFiller(euclidEnemyTitle, euclidEnemyDialogue);
						Euclid.StatRandomizer(150, 200, 15, 20, 0.1f, 0.15f);
						battleEngine.EnemyFiller(&Euclid);
						break;
					case 'k':
						menu.MenuTextBufferFiller(keterEnemyTitle, keterEnemyDialogue);
						Keter.StatRandomizer(250, 300, 25, 30, 0.2f, 0.25f);
						battleEngine.EnemyFiller(&Keter);
						break;
					case 'B':
						menu.MenuTextBufferFiller(johnnyBassEnemyTitle, johnnyBassDialogue);
						battleEngine.EnemyFiller(&JohnnyBass);
						break;
					}
					break;
				}
			}
		}
	}
}

void BattleHandler() {
	if (MC.inBattle) {
		battleEngine.BattleEngine();
	}
}