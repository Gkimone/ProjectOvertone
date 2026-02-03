#pragma once
#include "utils/ArrayHandler.h"

#include "Text.h"
#include "Navigation.h"
#include "Structs.h"

#include "Screens.h"

namespace Overtone {

	class Screen {
	private:
		//Private Variables	
		Navigation screenNav;

	public:
		//Public Variables
		Text screenText;
		char screen[HEIGHT][WIDTH];

	private:
		//Private Functions
		void BagScreenNav(int k, Inventory& thisBag, Stats& thisStats) {
			switch (k) {
			case 'z': case 'Z':
				switch (screenNav.opc) {
					//Use Med
				case 5:
					if (thisBag.med > 0 && thisStats.hp < thisStats.maxhp) {
						thisBag.med -= 1;
						thisStats.hp += 125;
						if (thisStats.hp > thisStats.maxhp) {
							thisStats.hp = thisStats.maxhp;
						}
					}
					break;
				}
				break;
			case 'x': case 'X':
				cW = lW;
				inNewZone = true;
				break;
			}
		}

		void ScreenCommands(int k, Inventory& thisBag, Stats& thisStats) {
			switch (cW) {
			case -3:
				BagScreenNav(k, thisBag, thisStats);
				break;
			}
		}

	public:
		//Public Functions
		void ScreenFiller(const char screenFiller[HEIGHT][WIDTH]) {
			for (int i = 0; i < HEIGHT; i++) {
				for (int j = 0; j < WIDTH; j++) {
					screen[i][j] = screenFiller[i][j];
				}
			}
		}

		void ScreenCoordFiller(const int x, const int y, const char glyph) {
			screen[y][x] = glyph;
		}

		void ScreenTextBufferFiller(const char title[WIDTH], const charMatrix& text) {
			screenText.TextBufferFiller(title, text);
			isTextOnScreen = true;
			screenText.isThereText = true;
		}

		void ScreenTextFiller() {
			screenText.InitTextSetup(screen);
			screenText.TextGen(screen);
		}

		void ScreenGen(string& frame) {
			for (int i = 0; i < HEIGHT; i++) {
				Utils::String_1x18_Filler(screen[i], frame);
			}
			std::cout << frame;
		}

		void ScreenKeyChecks(int k, int sK, Inventory& thisBag, Stats& thisStats) {
			if (k == 0 || k == 224) {
				screenNav.Nav(sK);
			}
			else {
				ScreenCommands(k, thisBag, thisStats);
			}

		}

		void ScreenNav() {
			ScreenCoordFiller(7, screenNav.opc, screenNav.glyph);
			if (screenNav.oldOpc != screenNav.opc) {
				ScreenCoordFiller(7, screenNav.oldOpc, '+');
			}
		}

		//Constructors
		Screen() : screenText(true), screenNav(5, 13, 4) {
			Utils::Char_18x18_ArrayFiller(emptyScreen, screen);
		}

	};
}
inline Overtone::Screen screen;
