#pragma once
namespace Overtone {
	class Navigation {
	public:
		//Public Variables
		const char glyph = '>';
		int minOpc, maxOpc, step, opc, oldOpc;
		
	public:
		//Public Functions
		void Nav(int k) {
			oldOpc = opc;
			switch (k) {
				//Up
			case 72:
				opc -= step;
				if (opc < minOpc) {
					opc = maxOpc;
				}
				break;
				//Down
			case 80:
				opc += step;
				if (opc > maxOpc) {
					opc = minOpc;
				}
				break;
			}
		}
		//Constructors
		Navigation() {
			minOpc = 0;
			maxOpc = 0;
			step = 0;
			opc = 0;
			oldOpc = 0;
		}

		Navigation(int min, int max, int stp) {
			minOpc = min;
			maxOpc = max;
			step = stp;
			opc = min;
			oldOpc = opc;
		}
	};
}