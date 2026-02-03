#pragma once
namespace Overtone {
	//Global Constants
	inline constexpr int 
		WIDTH = 18,
		HEIGHT = 18,
		M_HEIGHT = 9,
		//valid floors quantity
		vfq = 7;

	inline constexpr float fail = 0.1f;

	inline const char
		borderLine[WIDTH]	= { 'o', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'o' },
		spaceLine[WIDTH]	= { '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|' },
		floorChars[vfq]		= { ' ', '.', ';', '_', '^', '{', '}'};

	//Global Variables
	inline int
		//last World
		lW = 0,
		//current World/Floor/Zone
		cW = -1,
		cF = 0,
		cZ = 0;

	inline bool
		programIsRunning = true,

		isTextOnMenu = false,
		isTextOnScreen = false,
		isMenuOpen = false,
		inNewZone = false,

		sound = true,
		slowMode = true;
}