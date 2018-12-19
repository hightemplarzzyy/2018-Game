#include "HorizonColourCycle.h"

Color HorizonColorCycle::NIGHT_COLOR = Color(51, 51, 108, true);
Color HorizonColorCycle::DAY_COLOR = Color(0.6f, 0.9f, 1.0f);
Color HorizonColorCycle::DAWN_COLOR = Color(238, 124, 145, true);
Color HorizonColorCycle::DUSK_COLOR = Color(255, 160, 119, true);

float HorizonColorCycle::MIDNIGHT_END = 2.4f;
float HorizonColorCycle::MIDDAY_START = 12.0f;
float HorizonColorCycle::MIDDAY_END = 14.4f;