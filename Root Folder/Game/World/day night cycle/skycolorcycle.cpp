#include "SkyColorCycle.h"

Color SkyColorCycle::NIGHT_COLOR = Color(78, 113, 164, true);
Color SkyColorCycle::DAY_COLOR = Color(1, 0.87f, 0.6f);
Color SkyColorCycle::DAWN_COLOR = Color(254, 197, 145, true);
Color SkyColorCycle::DUSK_COLOR = Color(255, 239, 170, true);

float SkyColorCycle::MIDNIGHT_END = 2.4f;
float SkyColorCycle::MIDDAY_START = 12.0f;
float SkyColorCycle::MIDDAY_END = 14.4f;