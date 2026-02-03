#pragma once
#include "Config.h"
#include "classes/Structs.h"
#include "classes/Menu.h"
#include "Texts.h"

namespace Overtone {

	class Item {
	private:
		const char types[4] = { ' ', '*', ',', '?'};

	private:
		bool isBagFull(int items) {
			if (items > 99) {
				menu.MenuTextBufferFiller(interactionTitle, bagFullInteraction);
				return true;
			}
			else return false;
		}

	public:
		char GlyphChecker(int ID) {
			return types[ID];
		}
		void InteractionHandler(FeatureTile& FT, Inventory& thisBag) {
			switch (FT.typeID.intID) {
			case 1:
				if (!isBagFull(thisBag.med)) {
					thisBag.med += 1;
					FT.typeID.charID = 'n';
					menu.MenuTextBufferFiller(interactionTitle, medInteraction);
				}
				break;
			case 2:
				if (!isBagFull(thisBag.amm)) {
					thisBag.amm += 1;
					FT.typeID.charID = 'n';
					menu.MenuTextBufferFiller(interactionTitle, ammoInteraction);
				}
				break;
			case 3:
				if (!isBagFull(thisBag.key)) {
					thisBag.key += 1;
					FT.typeID.charID = 'n';
					menu.MenuTextBufferFiller(interactionTitle, keyInteraction);
				}
				break;
			}
		}
	};
}
inline Overtone::Item items;