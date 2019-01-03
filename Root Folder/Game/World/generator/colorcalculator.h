#pragma once
#pragma once

#include "..\..\Render Engine\toolbox\color.h"
#include "..\world config\worldconfigs.h"

#include <map>

using namespace std;

class ColorCalculator {
private:
	const Color SEA_COLOR = Color(214.0f, 237.0f, 146.0f, true);
	const Color COAST_COLOR = Color(210.0f, 193.0f, 134.0f, true);
	const Color BACK_COLOR = Color(111.0f, 80.0f, 45.0f, true);
	const Color SNOW_COLOR = Color(0.7f, 0.7f, 0.75f);

	map<float, Color> m_ColorProfile;

public:
	ColorCalculator();
	Color getColor(float height, WorldConfigs configs);    //获取height所在高度对应的颜色
};