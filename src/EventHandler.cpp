#include "EventHandler.h"
#include "BattleHandler.h"

#include "classes/Entities.h"
#include "classes/Map.h"

#include "Texts.h"

using Overtone::cW, Overtone::cF, Overtone::cZ;
using Overtone::FeatureTile;

bool interactedWithPhone = false;

//Coord Writer
void CW(int X, int Y, char glyph) {
	MC.pos.X = X;
	MC.pos.Y = Y;
	MC.oldPos.X = MC.pos.X; 
	MC.oldPos.Y = MC.pos.Y;
	MC.currentTile = glyph;
	MC.lastTile = MC.currentTile;
	MC.nextTile = MC.currentTile;
}

void ZoneResizer() {
	const Overtone::Map& currentWorld = lucidMap[cW];
	if (MC.currentWorldInt.size() < (size_t)currentWorld.mapFloor.size()) {
		MC.currentWorldInt.resize(currentWorld.mapFloor.size());
	}
	if (MC.currentWorldInt[cF].floorZone.size() < (size_t)currentWorld.mapFloor[cF].floorZone.size()) {
		MC.currentWorldInt[cF].floorZone.resize(currentWorld.mapFloor[cF].floorZone.size());
	}
}

void Zone1(int X, int Y) {
	switch (X) {
	case 17:
		cZ = 2;
		switch (Y) {
		case 10:	
			CW(1, 7, '.');
			break;
		case 11:
			CW(1, 8, '.');
			break;
		}
		break;
	case 10:
		cZ = 4;
		CW(10, 1, ' ');
		break;
	}
}
void Zone2(int X, int Y) {
	switch (X) {
	case 0:
		switch (Y) {
		case 7:
			cZ = 1;
			CW(16, 10, '.');
			break;
		case 8:
			cZ = 1;
			CW(16, 11, '.');
			break;
		case 15:
			cZ = 4;
			CW(16, 1, '.');
			break;
		case 16:
			cZ = 4;
			CW(16, 2, '.');
			break;
		}
		break;
	case 17:
		cZ = 3;
		switch (Y) {
		case 15:
			CW(1, 15, '.');
			break;
		case 16:
			CW(1, 16, '.');
			break;
		}
		break;

	case 4: 
		cZ = 5;
		switch (Y) {
		case 17:
			CW(4, 1, '.');
			break;
		}
		break;
	case 5:
		cZ = 5;
		switch (Y) {
		case 17:
			CW(5, 1, '.');
			break;
		}
		break;
	}
}
void Zone3(int X, int Y) {
	switch (X) {
	case 0:
		cZ = 2;
		switch (Y) {
		case 15:
			CW(16, 15, '.');
			break;
		case 16:
			CW(16, 16, '.');
			break;
		}
		break;
	}
}
void Zone4(int X, int Y) {
	switch (X) {
	case 17:
		switch (Y) {
		case 1:
			cZ = 2;
			CW(1, 15, '.');
			break;
		case 2:
			cZ = 2;
			CW(1, 16, '.');
			break;
		case 13:
			cZ = 5;
			CW(1, 10, '.');
			break;
		case 14:
			cZ = 5;
			CW(1, 11, '.');
			break;
		case 15:
			cZ = 5;
			CW(1, 12, '.');
			break;
		case 16:
			cZ = 5;
			CW(1, 13, '.');
			break;
		}
		break;
	case 16:
		switch (Y) {
		case 17:
			cZ = 7;
			CW(16, 1, '.');
			break;
		}
		break;
	case 15:
		switch (Y) {
		case 17:
			cZ = 7;
			CW(15, 1, '.');
			break;
		}
		break;
	case 13:
		switch (Y) {
		case 17:
			cZ = 7;
			CW(13, 1, ' ');
			break;
		}
		break;
	case 10:
		switch (Y) {
		case 0:
			cZ = 1;
			CW(10, 16, '.');
			break;
		}
		break;
	}
}
void Zone5(int X, int Y) {
	switch (X) {
	case 0:
		cZ = 4;
		switch (Y) {	
		case 10:
			CW(16, 13, '.');
			break;
		case 11:
			CW(16, 14, '.');
			break;
		case 12:
			CW(16, 15, '.');
			break;
		case 13:
			CW(16, 16, '.');
			break;
		}
		break;
	case 4:
		switch (Y) {
		case 0:
			cZ = 2;
			CW(4, 16, '.');
			break;
		}
		break;
	case 5:
		switch (Y) {
		case 0:
			cZ = 2;
			CW(5, 16, '.');
			break;
		}
		break;
	case 16:
		switch (Y) {
		case 15:
			cZ = 9;
			CW(8, 15, '.');
			break;
		case 16:
			cZ = 9;
			CW(8, 16, '.');
			break;
		}
		break;
	case 17:
		cZ = 6;
		switch (Y) {
		case 2:
			CW(1, 2, ' ');
			break;
		case 8:
			CW(1, 8, '.');
			break;
		case 9:
			CW(1, 9, '.');
			break;
		}
		break;
	}
}
void Zone6(int X, int Y) {
	switch (X) {
	case 0:
		cZ = 5;
		switch (Y) {
		case 2:
			CW(16, 2, '.');
			break;
		case 8:
			CW(16, 8, '.');
			break;
		case 9:
			CW(16, 9, '.');
			break;
		}
		break;
	}
}
void Zone7(int X, int Y) {
	switch (Y) {
	case 0:
		cZ = 4;
		switch (X) {
		case 13:
			CW(13, 16, '.');
			break;
		case 15:
			CW(15, 16, '.');
			break;
		case 16:
			CW(16, 16, '.');
			break;
		}
		break;
	case 15:
		switch (X) {
		case 17:
			cZ = 8;
			CW(1, 1, '.');
			break;
		}
		break;
	case 16:
		switch (X) {
		case 17:
			cZ = 8;
			CW(1, 2, '.');
			break;
		}
		break;
	}
}
void Zone8(int X, int Y) {
	switch (X) {
	case 0:
		switch (Y) {
		case 1:
			cZ = 7;
			CW(16, 15, '.');
			break;
		case 2:
			cZ = 7;
			CW(16, 16, '.');
			break;
		}
		break;
	}
}
void Zone9(int X, int Y) {
	switch (X) {
	case 7:
		switch (Y) {
		case 15:
			cZ = 5;
			CW(15, 15, '.');
			break;
		case 16:
			cZ = 5;
			CW(15, 16, '.');
			break;
		}
		break;
	case 8:
		switch (Y) {
		case 0:
			cZ = 10;
			CW(8, 16, '.');
			break;
		}
		break;
	case 9:
		switch (Y) {
		case 0:
			cZ = 10;
			CW(9, 16, '.');
			break;
		}
		break;
	}
}
void Zone10(int X, int Y) {
	switch (Y) {
	case 17:
		switch (X) {
		case 8:
			cZ = 9;
			CW(8, 1, '.');
			break;
		case 9:
			cZ = 9;
			CW(9, 1, '.');
			break;
		}
		break;
	}
}

void ZonePass(int X, int Y) {
	switch (cW) {
	case 0:
		switch(cZ) {
		case 0: 
			if (MC.nextTile != 't' && !interactedWithPhone) {
				menu.MenuTextBufferFiller(warningTitle, suggestion1);
			} 
			else if (MC.nextTile != 't' && interactedWithPhone) {
				cF = 1;
				cZ = 1;
				MC.tic = 0;
			}
			else if (MC.nextTile == 't' && !interactedWithPhone) {
				menu.MenuTextBufferFiller(theodoreTitle, introduction);
				interactedWithPhone = true;
			}
			else if (MC.nextTile == 't' && interactedWithPhone) {
				menu.MenuTextBufferFiller(warningTitle, suggestion2);
			}
			break;
		case 1:
			Zone1(X, Y);
			break;
		case 2:
			Zone2(X, Y);
			break;
		case 3:
			Zone3(X, Y);
			break;
		case 4:
			Zone4(X, Y);
			break;
		case 5:
			Zone5(X, Y);
			break;
		case 6:
			Zone6(X, Y);
			break;
		case 7:
			Zone7(X, Y);
			break;
		case 8:
			Zone8(X, Y);
			break;
		case 9:
			Zone9(X, Y);
			break;
		case 10:
			Zone10(X, Y);
			break;
		}
		ZoneResizer();
		break;
	}
}

void SpawnPoints() {
	if (cZ == 0) {
		screen.ScreenTextBufferFiller(prologueTitle, prologue);
		CW(12, 5, 'D');
		MC.tic = 1;
	}
	else {
		switch (cW) {
		case 0:
			//oG:
			CW(3, 2, 'T');
			//debug:
			//CW(1, 7, '.');
			break;
		}
	}
}

void EventHandler() {
	if (cW >= 0) {
		Overtone::BattleEncounter();
		if (MC.interacted && MC.nextTile == '=' || MC.interacted && MC.nextTile == '>' || MC.interacted && MC.nextTile == '<' || MC.interacted && MC.nextTile == 't') {
			ZonePass(MC.thisInteractive.tilePos.X, MC.thisInteractive.tilePos.Y);
		}
		if (MC.tic == 0) {
			SpawnPoints();
		}
	}
}