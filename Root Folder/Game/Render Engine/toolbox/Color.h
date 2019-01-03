#pragma once
#include "maths/maths_func.h"


class Color {
public:
	union {
		float channel[3];
		vec3 m_RGB;
	};
	float m_A;

public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, bool convert);
	Color(float r, float g, float b, float a);
	Color(const vec3 &color);

	static Color interpolateColors(const Color &maincolor, const Color &subcolor, float blend);
	void interpolate(const Color &subcolor, float blend);

	Color& add(const Color &other);
	Color& subtract(const Color &other);
	Color& multiply(const Color &other);
	Color& divide(const Color &other);

	friend Color operator+(Color leftColor, const Color &rightColor);
	friend Color operator-(Color leftColor, const Color &rightColor);
	friend Color operator*(Color leftColor, const Color &rightColor);
	friend Color operator/(Color leftColor, const Color &rightColor);

	Color& operator+=(const Color &other);
	Color& operator-=(const Color &other);
	Color& operator*=(const Color &other);
	Color& operator/=(const Color &other);
	bool operator==(const Color &other);
	bool operator!=(const Color &other);

};