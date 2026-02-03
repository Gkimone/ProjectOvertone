#pragma once
#include "utils/ArrayHandler.h"
#include "Config.h"

#include "Texts.h"

namespace Overtone {
	class Text {
	private:
		//Private Variables
		const int heightMargin = 2;

		int c = 0,
			lines = 0,
			linesDone = 0,
			linesLeft = 0,
			topLine = 0,
			botLine = 0,
			textSpeed = 0,
			defaultLines = 0;

		bool onScreen = false,
			wasMenuOpen = false;

		char textTitle[WIDTH];
		charMatrix textString;

	public:
		//Public Variables
		bool isThereText = false;

	private:
		//Private Funtions
		int TextHeight(const int H) {
			
			return ((H / heightMargin) + (H % heightMargin)) - heightMargin;
		}
		void SlowModeChecker() {
			if (slowMode) {
				textSpeed = 1;
			}
			else {
				textSpeed = TextHeight(defaultLines);
			}
		}
		void LinesChecker(const charMatrix& text) {
			if (lines == 0) {
				lines = textSpeed;
			} 
			else if (lines > static_cast<int>(text.size())) { 
				lines = static_cast<int>(text.size()); 
			}
		}

		void Reset() { 
			if (wasMenuOpen) {
				isMenuOpen = wasMenuOpen;
				wasMenuOpen = false;
			}
			c = 0; 
			lines = 0;
			linesDone = 0; 
			linesLeft = 0; 
			isThereText = false;
		}

		void TextCleaner(char emptyArray[][WIDTH]) {
			for (int i = topLine; i <= botLine; i++) {
				Utils::Char_1x18_ArrayFiller(spaceLine, emptyArray[i]);
			}
			Utils::Char_1x18_ArrayFiller(borderLine, emptyArray[botLine]);
		}
		void TitleFiller(char emptyArray[][WIDTH]) {
			Utils::Char_1x18_ArrayFiller(textTitle, emptyArray[topLine]);
		}
		void LineFiller(const charVector& text, char emptyArray[WIDTH]) {
			for (int j = 0; j < WIDTH; j++) {
				emptyArray[j] = text[j];
			}
		}
	public:
		//Public Functions
		void TextBufferFiller(const char title[WIDTH], const charMatrix& text) {
			Utils::Char_1x18_ArrayFiller(title, textTitle);
			textString = text;
			textString.shrink_to_fit();
		}

		void InitTextSetup(char emptyArray[][WIDTH]) {
			if (c == 0 || c >= botLine) {
				if (isMenuOpen) {
					wasMenuOpen = isMenuOpen;
					isMenuOpen = false;
				}
				SlowModeChecker();
				c = topLine + heightMargin;
				TextCleaner(emptyArray);
				TitleFiller(emptyArray);
				
			}
		}

		void TextGen(char emptyArray[][WIDTH]) {
			InitTextSetup(emptyArray);
			linesLeft = static_cast<int>(textString.size()) - linesDone;

			if (linesLeft <= 0 || isThereText == false) {
				Reset();
			}
			else if (linesLeft <= textSpeed) {
				linesLeft = static_cast<int>(textString.size());
				for (int i = linesDone; i < linesLeft; i++) {
					LineFiller(textString[i], emptyArray[c]);
					c += heightMargin;
				}
				Utils::Char_1x18_ArrayFiller(borderLine, emptyArray[botLine]);
				Reset();
			}
			else {
				LinesChecker(textString);

				for (int i = linesDone; i < lines; i++) { 
					LineFiller(textString[i], emptyArray[c]);
					c += heightMargin; 
				} 
				Utils::Char_1x18_ArrayFiller(borderLine, emptyArray[botLine]); 

				linesDone = lines; 
				lines += textSpeed;
			}
		}
	
	public:
		//Constructors
		Text() :
			c(0),
			lines(0),
			linesDone(0),
			linesLeft(0),
			topLine(0),
			botLine(M_HEIGHT - 1),
			textSpeed(0),
			defaultLines(M_HEIGHT),
			onScreen(false)
		{
			Utils::Char_1x18_ArrayFiller(spaceLine, textTitle);
		}

		Text(bool isOnScreen) :
			c(0),
			lines(0),
			linesDone(0),
			linesLeft(0),
			onScreen(isOnScreen)
		{
			Utils::Char_1x18_ArrayFiller(spaceLine, textTitle);

			if (onScreen) {
				topLine = 1;
				botLine = HEIGHT - 1;
				defaultLines = HEIGHT;
			}
			else {
				topLine = 0;
				botLine = M_HEIGHT - 1;
				defaultLines = M_HEIGHT;
			}
		}
	};
};