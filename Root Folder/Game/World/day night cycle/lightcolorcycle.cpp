#include "LightColorCycle.h"

Color LightColorCycle::NIGHT_COLOR = Color(0.35f, 0.38f, 0.8f);
Color LightColorCycle::DAY_COLOR = Color(1.0f, 0.95f, 0.95f);
Color LightColorCycle::DAWN_COLOR = Color(1.0f, 0.45f, 0.56f);
Color LightColorCycle::DUSK_COLOR = Color(1.0f, 0.87f, 0.6f);

float LightColorCycle::MIDNIGHT_END = 2.4f;
float LightColorCycle::MIDDAY_START = 12.0f;
float LightColorCycle::MIDDAY_END = 14.4f;