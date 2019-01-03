#pragma once

#include "ColorCycle.h"

class LightColorCycle :public ColorCycle {
private:
	static Color NIGHT_COLOR;
	static Color DAY_COLOR;
	static Color DAWN_COLOR;
	static Color DUSK_COLOR;

	static float MIDNIGHT_END;
	static float MIDDAY_START;
	static float MIDDAY_END;

public:
	LightColorCycle() :
		ColorCycle(NIGHT_COLOR, DAY_COLOR, DAWN_COLOR, DUSK_COLOR,
			MIDNIGHT_END, MIDDAY_START, MIDDAY_END) {

	}
};






