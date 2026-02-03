#include "Config.h"
#include "EntityHandler.h"

#include "classes/Entities.h"
#include "classes/Structs.h"

const char enemies[enemyTypes]{' ', 's', 'e', 'k'};

char EntityGlyphChecker(int ID) {
	switch (ID) {
	case 4:
		return JohnnyBass.glyph;
	case 5:
		return Dorothy.glyph;
	case 6:
		return Theodore.glyph;
	default:
		return enemies[ID];
	}
}