#include "utils/ArrayHandler.h"

#include "classes/Map.h"
#include "EntityHandler.h"

using Overtone::Map, Overtone::ObjectID;
using Overtone::WIDTH, Overtone::HEIGHT;
using Overtone::cW, Overtone::cF, Overtone::cZ;

enum WorldsEnum { w0 };
enum FloorsEnum { f0, f1 };
enum ZonesEnum { z0, z1, z2, z3, z4, z5, z6, z7, z8, z9, z10};

void MapInit(Map& exampleMap, const int floorID, const int zoneID, const char zoneMap[HEIGHT][WIDTH], const FeatureTileVector& tempI) {
	exampleMap.InitIndividualZone(floorID, zoneID, zoneMap, tempI);
}

void InitWorlds() {
	MapInit(lucidMap[w0], f1, z1, w0f1z1, temp_w0f1z1);
	MapInit(lucidMap[w0], f1, z2, w0f1z2, temp_w0f1z2);
	MapInit(lucidMap[w0], f1, z3, w0f1z3, temp_w0f1z3);
	MapInit(lucidMap[w0], f1, z4, w0f1z4, temp_w0f1z4);
	MapInit(lucidMap[w0], f1, z5, w0f1z5, temp_w0f1z5);
	MapInit(lucidMap[w0], f1, z6, w0f1z6, temp_w0f1z6);
	MapInit(lucidMap[w0], f1, z7, w0f1z7, temp_w0f1z7);
	MapInit(lucidMap[w0], f1, z8, w0f1z8, temp_w0f1z8);
	MapInit(lucidMap[w0], f1, z9, w0f1z9, temp_w0f1z9);
	MapInit(lucidMap[w0], f1, z10, w0f1z10, temp_w0f1z10);
}

//	The Tile IDs work this way:
//	First char identifies if its an Item, an interactable tile or an entity:
//	i = Item
//	t = Tile
//	e = Entity
//	n = Nothing;

char TileChecker(ObjectID& ID) {
	char tile = ' ';
	switch (ID.charID) {
	case 'i': case 'I':
		tile = items.GlyphChecker(ID.intID); 
		break;
	case 't': case 'T':
		tile = interactiveTiles.GlyphChecker(ID.intID); 
		break;
	case 'e': case 'E':
		tile = EntityGlyphChecker(ID.intID); 
		break;
	}
	return tile;
}

void TileMapper(Map& thisWorld) {
	for (int i = 0; i < thisWorld.mapFloor[cF].floorZone[cZ].zoneInt.size(); i++) {
		Overtone::Zone& thisZone = thisWorld.mapFloor[cF].floorZone[cZ];
		Overtone::ObjectID& tileType = thisZone.zoneInt[i].typeID;
		int tileX = thisZone.zoneInt[i].tilePos.X, tileY = thisZone.zoneInt[i].tilePos.Y;
		
		screen.ScreenCoordFiller(tileX, tileY, TileChecker(tileType));
	}
}
void TilesUpdater(Map& thisWorld) {
	TileMapper(thisWorld);
	for (int i = 0; i < MC.currentWorldInt[cF].floorZone[cZ].usedInt.size(); i++) {
		Overtone::Zone& thisZone = thisWorld.mapFloor[cF].floorZone[cZ];
		Overtone::ObjectID& 
			tileType = MC.currentWorldInt[cF].floorZone[cZ].usedInt[i].typeID;
		int tileX = MC.currentWorldInt[cF].floorZone[cZ].usedInt[i].tilePos.X, 
			tileY = MC.currentWorldInt[cF].floorZone[cZ].usedInt[i].tilePos.Y;

		screen.ScreenCoordFiller(tileX, tileY, TileChecker(tileType));
	}

}

//Interactables Circumstantial Checker
void ICC(Map& thisWorld) {
	if (Overtone::inNewZone || MC.interacted) {
		thisWorld.MapFiller(screen);
		if (MC.currentWorldInt.empty() == false) {
			if (MC.currentWorldInt[cF].floorZone[cZ].interacted) {
				TilesUpdater(thisWorld);
			}
			else {
				TileMapper(thisWorld);
			}
		}
		else {
			TileMapper(thisWorld);
		}
		Overtone::inNewZone = false;
		MC.interacted = false;
	}
}

void MapHandler() {
	Map& thisWorld = lucidMap[cW];
	ICC(thisWorld);
	MC.Draw(screen);
}