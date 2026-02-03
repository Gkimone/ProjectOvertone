#pragma once
#include "utils/ArrayHandler.h"

#include "Text.h"
#include "Navigation.h"

#include "Menus.h"

namespace Overtone {
	class Menu {
	public:
		//Public Variables
		char menu[M_HEIGHT][WIDTH];
		Navigation menuNav;
		Text menuText;

	private:
		//Private Functions
		void MainMenuNav(int k) {
			switch (k) {
			case 'z': case 'Z':
				switch (menuNav.opc) {
					//play
				case 2:
					cW = 0;
					cF = 0;
					cZ = 0;
					isMenuOpen = false;
					inNewZone = true;
					break;
					//Config
				case 4:
					lW = cW;
					cW = -2;
					break;
					//Exit
				case 6:
					programIsRunning = false;
					break;
				}
				break;
			}
		}
		void ConfigMenuNav(int k) {
			switch (k) {
			case 'z': case 'Z':
				switch (menuNav.opc) {
					//sound On/Off
				case 2:
					if (sound) {
						sound = false;
					}
					else {
						sound = true;
					}
					break;
					//slow mode On/Off
				case 4:
					if (slowMode) {
						slowMode = false;
					}
					else {
						slowMode = true;
					}
					break;
					//back
				case 6:
					cW = lW;
					if (cW >= 0) {
						isMenuOpen = false;
					}
					break;
				}
				break;
			}
		}

		void MenuCommands(int k) {
			switch (cW) {
			case -1:
				MainMenuNav(k);
				break;
			case -2:
				ConfigMenuNav(k);
				break;
			}
		}

	public:
		//Public Funtions
		void MenuFiller(const char menuFiller[M_HEIGHT][WIDTH]) {
			for (int i = 0; i < M_HEIGHT; i++) {
				Utils::Char_1x18_ArrayFiller(menuFiller[i], menu[i]);
			}
		}

		void MenuCoordFiller(const int x, const int y, const char glyph) {
			menu[y][x] = glyph;
		}

		void MenuTextBufferFiller(const char title[WIDTH], const charMatrix& text) {
			menuText.TextBufferFiller(title, text);
			isTextOnMenu = true;
			menuText.isThereText = true;
		}

		void MenuTextFiller() {
			menuText.InitTextSetup(menu);
			menuText.TextGen(menu);
		}

		void MenuGen(string& frame) {
			for (int i = 0; i < M_HEIGHT; i++) {
				Utils::String_1x18_Filler(menu[i], frame);
			}
			std::cout << frame;
		}

		void MenuKeyChecks(int k, int sK) {
			if (k == 0 || k == 224) {
				menuNav.Nav(sK);
			}
			else {
				MenuCommands(k);
			}
			
		}

		void MenuNav() {
			MenuCoordFiller(2, menuNav.opc, menuNav.glyph);
			if (menuNav.oldOpc != menuNav.opc) {
				MenuCoordFiller(2, menuNav.oldOpc, ' ');
			}
		}

		//Constructors
		Menu() : menuText(false), menuNav(2, 6, 2) {
			MenuFiller(emptyMenu);
		}
	};
}
inline Overtone::Menu menu;