#pragma once

#include <map>

#include "../../Render Engine/toolbox/Color.h"

class ColorCycle {
private:
	Color m_nightColor;
	Color m_dayColor;
	Color m_dawnColor;	//ÀèÃ÷
	Color m_duskColor;	//»Æ»è

	float m_midnightEnd;
	float m_middayStart;
	float m_middayEnd;

	std::map<float, Color> m_colors;

	void create() {
		m_colors[0.0f] = m_nightColor;
		m_colors[m_middayEnd] = m_nightColor;
		m_colors[m_middayEnd + (m_middayEnd - m_middayStart) * 0.5f] = m_dawnColor;
		m_colors[m_middayStart] = m_dayColor;
		m_colors[m_middayEnd] = m_dayColor;
		m_colors[m_middayEnd + (1 - m_middayEnd)*0.5f] = m_duskColor;
		m_colors[1.0f] = m_nightColor;
	}

public:
	ColorCycle(Color nightColor, Color dayColor, Color dawnColor, Color duskColor,
		float midnightEnd, float middayStart, float middayEnd) {
		m_nightColor = nightColor;
		m_dayColor = dayColor;
		m_dawnColor = dawnColor;
		m_duskColor = duskColor;

		m_midnightEnd = midnightEnd / 24.0f;
		m_middayStart = middayStart / 24.0f;
		m_middayEnd = middayEnd / 24.0f;

		create();
	}

	Color getColor(float time) {
		std::map<float, Color> ::iterator it;
		float pre, next;
		for (it = m_colors.begin(); it != m_colors.end(); it++) {
			if (it->first > time) {
				next = it->first;
				break;
			}
			pre = it->first;
		}
		float blend = (time - pre) / (next - pre);
		return Color::interpolateColors(m_colors[pre], m_colors[next], blend);
	}

	
};
