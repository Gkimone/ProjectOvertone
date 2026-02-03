#include "Config.h"
#include "utils/ArrayHandler.h"

#include "classes/Entities.h"
#include "classes/Map.h"
#include "classes/Tile.h"
#include "classes/Item.h"
#include "classes/Structs.h"
#include "classes/Screen.h"

#include "EventHandler.h"
#include "EntityHandler.h"

namespace Overtone {
	bool InvalidTile() {
		for (int i = 0; i < vfq; i++) {
			if (floorChars[i] == MC.nextTile) {
				return false;
			}
		}
		return true;
	}

	//Is Interactive Tile
	bool IIT() {
		if (MC.nextTile == '=' || MC.nextTile == '<' || MC.nextTile == '>') {
			return true;
		}
		else if (InvalidTile()) {
			FeatureTile& newTile = MC.thisInteractive;
			const Map& currentWorld = lucidMap[cW];
			for (size_t i = 0; i < currentWorld.mapFloor[cF].floorZone[cZ].zoneInt.size(); i++) {
				const FeatureTile& currentTile = currentWorld.mapFloor[cF].floorZone[cZ].zoneInt[i];
				if (newTile.tilePos.X == currentTile.tilePos.X && newTile.tilePos.Y == currentTile.tilePos.Y) {
					newTile.typeID.charID = currentTile.typeID.charID;
					newTile.typeID.intID = currentTile.typeID.intID;
					return true;
				}
			}
			newTile.tilePos.X = 0;
			newTile.tilePos.Y = 0;
			return false;
		}
		return false;
	}

	void IDChecker(FeatureTile& FT) {
		switch (FT.typeID.charID) {
		case 'i': case 'I':
			items.InteractionHandler(FT, MC.bag);
			break;
		case 't': case 'T':
			interactiveTiles.InteractionHandler(FT, MC.bag);
			break;
		}
	}

	void ScreenStatWritter(int XposMin, int XposMax, int Ypos, int num) {
		for (int i = XposMin; i <= XposMax; i++) {
			screen.ScreenCoordFiller(i, Ypos, Utils::IntToCharLength3(num, i));
		}
	}

	void ShowBag() {
		//HP
		ScreenStatWritter(4, 6, 4, MC.stats.hp);
		screen.ScreenCoordFiller(5, 5, '/');
		ScreenStatWritter(4, 6, 6, MC.stats.maxhp);
		//ATK
		ScreenStatWritter(5, 6, 9, MC.stats.atk);
		//CRI
		ScreenStatWritter(5, 6, 13, (int)(MC.stats.cri * 100));
		//MEDS
		ScreenStatWritter(14, 16, 5, MC.bag.med);
		//AMMO
		ScreenStatWritter(14, 16, 9, MC.bag.amm);
		//KEY
		ScreenStatWritter(14, 16, 13, MC.bag.key);
	}

	void InteractionHandler() {
		const Overtone::Map& currentWorld = lucidMap[cW];
		if (MC.currentWorldInt.size() < currentWorld.mapFloor.size()) {
			MC.currentWorldInt.resize(currentWorld.mapFloor.size());
		}

		if (MC.currentWorldInt[cF].floorZone.size() < currentWorld.mapFloor[cF].floorZone.size()) {
			MC.currentWorldInt[cF].floorZone.resize(currentWorld.mapFloor[cF].floorZone.size());
		}
		const size_t cS = MC.currentWorldInt[cF].floorZone[cZ].usedInt.size() + (size_t)1;
		MC.currentWorldInt[cF].floorZone[cZ].usedInt.resize(cS);

		IDChecker(MC.thisInteractive);

		MC.currentWorldInt[cF].floorZone[cZ].interacted = true;
		MC.nextTile = MC.currentTile;
		MC.currentWorldInt[cF].floorZone[cZ].usedInt[cS - 1].tilePos.X = MC.thisInteractive.tilePos.X;
		MC.currentWorldInt[cF].floorZone[cZ].usedInt[cS - 1].tilePos.Y = MC.thisInteractive.tilePos.Y;
		MC.currentWorldInt[cF].floorZone[cZ].usedInt[cS - 1].typeID.charID = MC.thisInteractive.typeID.charID;
		MC.currentWorldInt[cF].floorZone[cZ].usedInt[cS - 1].typeID.intID = MC.thisInteractive.typeID.intID;
	}
}