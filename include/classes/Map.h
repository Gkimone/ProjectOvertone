#pragma once
#include "utils/ArrayHandler.h"
#include "classes/Structs.h"

#include "classes/Screen.h"
#include "classes/Entities.h"
#include "classes/Item.h"
#include "classes/Tile.h"

#include "Maps.h"

namespace Overtone {
	//Maps
	struct Zone {
		char zone[HEIGHT][WIDTH];
		//Zone Interactives
		std::vector<FeatureTile> zoneInt;

		Zone() {
			Utils::Char_18x18_ArrayFiller(exampleZone, zone);
			zoneInt.clear();
		}
	};
	struct Floor {
		std::vector<Zone> floorZone;
		int zones;

		Floor() {
			zones = 1;
			floorZone.reserve(zones);
		}
	};

	class Map {
	private:
		int world;

	public:
		int floors;
		std::vector<Floor> mapFloor;

	public:
		void InitIndividualZone(const int floorID, const int zoneID, const char zone[HEIGHT][WIDTH], const std::vector<FeatureTile>& tempZoneI) {
			if (floorID >= mapFloor.size()) {
				floors += 1;
				mapFloor.resize(floors);
			}
			if (zoneID >= mapFloor[floorID].floorZone.size()) {
				mapFloor[floorID].zones += 1;
				mapFloor[floorID].floorZone.resize(mapFloor[floorID].zones);
			}
			Utils::Char_18x18_ArrayFiller(zone, mapFloor[floorID].floorZone[zoneID].zone);
			mapFloor[floorID].floorZone[zoneID].zoneInt = tempZoneI;
		}

		void MapFiller(Screen& thisScreen) {
			thisScreen.ScreenFiller(mapFloor[cF].floorZone[cZ].zone);
		}

	public:
		//Default constructor:
		Map() {
			world = 0;
			floors = 0;
			mapFloor.clear();
		}
		//World_Floor Specifier
		Map(int WORLD) {
			world = WORLD;
			floors = 1;
			mapFloor.reserve(floors);
			InitIndividualZone(0, 0, zone0, tempI0);
		}
	};
}
	// lucidMap contains every world, floor and zone thats in the game:
	// Every instance inside this vector is one world
inline std::vector<Overtone::Map> lucidMap{ Overtone::Map(0) };