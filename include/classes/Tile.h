#pragma once
#include "Config.h"
#include "utils/ArrayHandler.h"
#include "classes/Structs.h"
#include "classes/Menu.h"
#include "Texts.h"

namespace Overtone {
	class Tile {
	private:
		const char types[4] = { ' ', ':', ';', '%'};

	public:
		char GlyphChecker(int ID) {
			return types[ID];
		}

		void InteractionHandler(FeatureTile& FT, Inventory& thisBag) {
			switch (FT.typeID.intID) {
			case 1:
				FT.typeID.intID = 2;
				menu.MenuTextBufferFiller(interactionTitle, doorInteraction);
				break;
			case 3:
				if (thisBag.key <= 0) {
					menu.MenuTextBufferFiller(interactionTitle, lockedDoor1Interaction);
				}
				else {
					FT.typeID.charID = 'n';
					menu.MenuTextBufferFiller(interactionTitle, lockedDoor2Interaction);
					thisBag.key -= 1;
					if (thisBag.key < 0) thisBag.key = 0;
				}
				break;
			}
		}
	};
}
inline Overtone::Tile interactiveTiles;