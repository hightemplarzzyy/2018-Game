#pragma once
#include "maths/maths_func.h"


class Color {
private:
	vec3 color;
	float a = 1.0f;
public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, bool convert);
	Color(float r, float g, float b, float a);
	Color(vec3 col);

	vec3 getColor();
	float getR();
	float getG();
	float getB();

	void setColor(float r, float g, float b);
	void setColor(float r, float g, float b, float a);
	void setColor(vec3 col);
	void setR(float r);
	void setG(float g);
	void setB(float b);

	static Color interpolateColors(Color color1, Color color2, float blend);

	friend Color operator+(Color leftColor, Color &rightColor);
	friend Color operator-(Color leftColor, Color &rightColor);
	friend Color operator*(Color leftColor, Color &rightColor);
	friend Color operator/(Color leftColor, Color &rightColor);

	Color add(Color col);
	Color sub(Color col);
	Color multiply(Color col);
	Color div(Color col);

	void operator+=(Color col);
	void operator-=(Color col);
	void operator*=(Color col);
	void operator/=(Color col);
};