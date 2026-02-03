#pragma once
#include "Config.h"
#include "utils/Randomizer.h"
#include "utils/ArrayHandler.h"

#include "classes/Structs.h"
#include "classes/Entities.h"
#include "classes/Menu.h"
#include "classes/Map.h"

#include "Texts.h"

namespace Overtone {
	class Battle {
	private:
		const int bulletDMG = 70;
		charMatrix log;
		charVector dmgLog{ '|', ' ', ' ', ' ', ' ', ' ', 'd', 'a', 'm', 'a', 'g', 'e', '.', ' ', ' ', ' ', ' ', '|' };

	public:
		Enemy* thisEnemy = nullptr;
		bool enemyTurn = false, playerTurn = false, shot = false, heal = false;
		int incomingDMG,
			outgoingDMG;

		Battle() : thisEnemy(nullptr), incomingDMG(0), outgoingDMG(0) {}

	private:
		bool Failure() {
			if (!Rand::chance(fail)) {
				return false;
			}
			return true;
		}

		void logFiller(const charMatrix& thisText, int dmg) {
			int c = 1;
			log = thisText;

			for (int i = 1; i < 4; i++) {
				dmgLog[i] = Utils::IntToCharLength3(dmg, c);
				c++;
			}
			log.push_back(dmgLog);
			menu.MenuTextBufferFiller(logTitle, log);
		}

		void EnemyDead() {
			if (MC.currentWorldInt.empty()) {
				MC.currentWorldInt.resize(cF + 1);
			}
			if (MC.currentWorldInt[cF].floorZone.empty()) {
				MC.currentWorldInt[cF].floorZone.resize(cZ + 1);
			}
			if (MC.currentWorldInt[cF].floorZone[cZ].usedInt.empty()) {
				MC.currentWorldInt[cF].floorZone[cZ].usedInt.resize(1);
			}
			const size_t cS = MC.currentWorldInt[cF].floorZone[cZ].usedInt.size() + (size_t)1;
			MC.currentWorldInt[cF].floorZone[cZ].usedInt.resize(cS);
			MC.interacted = true;
			MC.currentWorldInt[cF].floorZone[cZ].interacted = true;
			MC.currentWorldInt[cF].floorZone[cZ].usedInt[cS - 1] = { MC.thisInteractive.tilePos.X, MC.thisInteractive.tilePos.Y, 'n', 0 };

			enemyTurn = false;
			playerTurn = false;
			MC.inBattle = false;
			isMenuOpen = false;
			cW = lW;
		}

		void BattleCommands(int k) {
			switch (k) {
			case 'z': case 'Z':
				switch (menu.menuNav.opc) {
					//Punch
				case 2:
					outgoingDMG = MC.stats.atk;
					break;
					//Shoot
				case 4:
					if (MC.bag.amm > 0) {
						MC.bag.amm -= 1;
						shot = true;
					}
					else {
						return;
					}
					break;
					//Heal
				case 6:
					if (MC.bag.med > 0 && MC.stats.hp < MC.stats.maxhp) {
						MC.bag.med -= 1;
						MC.stats.hp += 125;
						heal = true;
						if (MC.stats.hp > MC.stats.maxhp) {
							MC.stats.hp = MC.stats.maxhp;
						}
					}
					else {
						return;
					}
					break;
				}
				break;
			}
			isMenuOpen = false;
			playerTurn = true;
		}

		void EnemyAction() {
			if (thisEnemy == nullptr) return;
			if (Failure()) {
				menu.MenuTextBufferFiller(logTitle, enemyAttackFail);
				incomingDMG = 0;
			}
			else {
				incomingDMG = thisEnemy->stats.atk;
				if (Rand::chance(thisEnemy->stats.cri)) {
					incomingDMG += (int)(thisEnemy->stats.atk * thisEnemy->stats.cri);
					logFiller(enemyAttackCrit, incomingDMG);
				}
				else {
					logFiller(enemyAttackSuccess, incomingDMG);
				}
			}
			MC.stats.hp -= incomingDMG;
			if (MC.stats.hp <= 0) {
				MC.stats.hp = 0;
				MC.alive = false;
			}
			incomingDMG = 0;
		}

		void PlayerAction() {
			if (heal) {
				menu.MenuTextBufferFiller(logTitle, playerHeal);
				heal = false;
			}
			else if (Failure()) {
				menu.MenuTextBufferFiller(logTitle, playerAttackFail);
				outgoingDMG = 0;
			}
			else {
				if (shot) {
					outgoingDMG += bulletDMG;
					if (Rand::chance(MC.stats.cri)) {
						outgoingDMG += (int)(bulletDMG * MC.stats.cri);
						logFiller(playerShotCrit, outgoingDMG);
					}
					else {
						logFiller(playerShotSuccess, outgoingDMG);
					}
					shot = false;
				}
				else {	
					outgoingDMG += MC.stats.atk;
					if (Rand::chance(MC.stats.cri)) {
						outgoingDMG += (int)(MC.stats.atk * MC.stats.cri);
						logFiller(playerAttackCrit, outgoingDMG);
					}
					else {
						logFiller(playerAttackSuccess, outgoingDMG);
					}
				}
			}
			thisEnemy->stats.hp -= outgoingDMG;
			if (thisEnemy->stats.hp <= 0) {
				thisEnemy->stats.hp = 0;
				thisEnemy->alive = false;
			}
		}

	public:
		void EnemyFiller(Enemy* newEnemy) {
			thisEnemy = newEnemy;
		}
		void BattleKeyChecks(int k, int sK) {
			if (k == 0 || k == 224) {
				menu.menuNav.Nav(sK);
			}
			else {
				BattleCommands(k);
			}
		}
		void BattleEngine() {
			if (isTextOnMenu) return;
			if (thisEnemy->alive && MC.alive) {
				incomingDMG = 0;
				outgoingDMG = 0;
				if (playerTurn) {
					PlayerAction();
					playerTurn = false;
					enemyTurn = true;
				}
				else if (enemyTurn) {
					EnemyAction();
					isMenuOpen = true;
					enemyTurn = false;
				}
			}
			if (isTextOnMenu) return;
			if (thisEnemy->glyph != JohnnyBass.glyph) {
				if (!MC.alive) {
					cW = -5;
					isMenuOpen = false;
				}
				if (!thisEnemy->alive) {
					EnemyDead();
				}
			}
			else {
				if (!MC.alive || !thisEnemy->alive) {
					cW = -6;
					menu.MenuTextBufferFiller(finaleTitle, finale);
					isMenuOpen = false;
					inNewZone = true;
				}	
			}
		}
	};
} inline Overtone::Battle battleEngine;