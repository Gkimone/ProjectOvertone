#pragma once
#include "utils/ArrayHandler.h"
#include "utils/Randomizer.h"

#include "classes/Screen.h"
#include "classes/Structs.h"
#include "Player.h"

namespace Overtone {
	class Entity {
	public:
		XY pos;
		int tic = 0;
		char glyph = '&';
		bool alive = true;

		//Constructor
		Entity() = default;
	};

	class Player : public Entity {
	public:
		Stats stats;
		Inventory bag;
		XY oldPos;
		char lastTile, currentTile, nextTile;
		bool inBattle, canInteract, interacted;
		std::vector<CurrentFloorChk> currentWorldInt;
		FeatureTile thisInteractive;

		//Constructor
		Player() : stats(250, 25, 0.2f) {
			glyph = '@';
			inBattle = false;
			interacted = false;
			canInteract = false;
			lastTile = glyph;
			currentTile = glyph;
			nextTile = glyph;
			currentWorldInt.clear();
		}
	private:
		bool OutOfScreen() {
			if (pos.X == WIDTH - 1 || pos.X == 0 || pos.Y == HEIGHT - 1 || pos.Y == 0) return true;
			else return false;
		}

		bool PosFixer() {
			if (OutOfScreen() || InvalidTile()) {
				pos.X = oldPos.X;
				pos.Y = oldPos.Y;
				return false;
			}
			else return true;
			
		}
		void Movement(int k, Screen& thisScreen) {
			tic += 1;
			oldPos.Y = pos.Y;
			oldPos.X = pos.X;
			switch (k) {
			case 72:
				pos.Y -= 1;
				break;
			case 75:
				pos.X -= 1;
				break;
			case 77:
				pos.X += 1;
				break;
			case 80:
				pos.Y += 1;
				break;
			}
			thisInteractive.tilePos.X = pos.X;
			thisInteractive.tilePos.Y = pos.Y;
			nextTile = thisScreen.screen[thisInteractive.tilePos.Y][thisInteractive.tilePos.X];
			canInteract = IIT();
			if (PosFixer()) {
				lastTile = currentTile;
				currentTile = nextTile;
			}
		}
		void Commands(int k) {
			tic += 1;
			switch (k) {
			case 'z': case 'Z':
				if (canInteract) {
					interacted = true;
					canInteract = false;
					if (nextTile != '=' && nextTile != '>' && nextTile != '<' && nextTile != 't') {
						InteractionHandler();
					}
				}
				break;
			case 'x': case 'X':
				canInteract = false;
				lW = cW;
				cW = -3;
				break;
			case 'c': case 'C':
				lW = cW;
				cW = -2;
				break;
			}
		}

	public:
		void KeyChecks(int k, int sK, Screen& thisScreen) {
			if (k == 0 || k == 224) {
				Movement(sK, thisScreen);
			}
			else {
				Commands(k);
			}
		}

		void Draw(Screen& thisScreen) {
			thisScreen.ScreenCoordFiller(oldPos.X, oldPos.Y, lastTile);
			thisScreen.ScreenCoordFiller(pos.X, pos.Y, glyph);
		}
	};

	class Enemy : public Entity {
	public:
		Stats stats;
	
		void StatRandomizer(int hpMin, int hpMax, int atkMin, int atkMax, float criMin, float criMax) {
			alive = true;
			stats.maxhp = Rand::getInt(hpMin, hpMax);
			stats.hp = stats.maxhp;
			stats.atk = Rand::getInt(atkMin, atkMax);
			stats.cri = Rand::getFloat(criMin, criMax);
		}

		//Constructor
		Enemy() : stats(100, 10, 0.1f) { glyph = 'i'; }
		Enemy(char CHAR) { glyph = CHAR; }
		Enemy(char CHAR, int HPMAX, int ATK, float CRI) : stats(HPMAX, ATK, CRI) 
		{ glyph = CHAR; }
	};

	class NPC : public Entity{
	public:
		NPC() { glyph = '&'; }
		NPC(char CHAR) { glyph = CHAR; }
	};
}
inline Overtone::Player MC;
inline Overtone::Enemy Safe('s'), Euclid('e'), Keter('k');
inline Overtone::Enemy JohnnyBass('B', 1000, 70, 0.45f);
inline Overtone::NPC Dorothy('d'), Theodore('t');