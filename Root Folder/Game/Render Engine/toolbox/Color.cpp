#include "Color.h"

Color::Color() {
	m_A = 1.0f;
}

Color::Color(float r, float g, float b) {
	channel[0] = r;
	channel[1] = g;
	channel[2] = b;
	m_A = 1.0f;
}

Color::Color(float r, float g, float b, bool convert) {
	channel[0] = r / 255.0f;
	channel[1] = g / 255.0f;
	channel[2] = b / 255.0f;
	m_A = 1.0f;
}

Color::Color(const vec3 &color) {
	m_RGB = color;
	m_A = 1.0f;
}

Color::Color(float r, float g, float b, float a) {
	channel[0] = r;
	channel[1] = g;
	channel[2] = b;
	m_A = a;
}

Color Color::interpolateColors(const Color &maincolor, const Color &subcolor, float blend) {
	Color result;

	result.channel[0] = (1 - blend) * subcolor.channel[0] + blend * maincolor.channel[0];
	result.channel[1] = (1 - blend) * subcolor.channel[1] + blend * maincolor.channel[1];
	result.channel[2] = (1 - blend) * subcolor.channel[2] + blend * maincolor.channel[2];

	return result;
}

void Color::interpolate(const Color &subcolor, float blend) {

	channel[0] = (1 - blend) * subcolor.channel[0] + blend * channel[0];
	channel[1] = (1 - blend) * subcolor.channel[1] + blend * channel[1];
	channel[2] = (1 - blend) * subcolor.channel[2] + blend * channel[2];
	return;
}


Color& Color::add(const Color &other) {
	channel[0] += other.channel[0];
	channel[1] += other.channel[1];
	channel[2] += other.channel[2];

	return *this;
}

Color& Color::subtract(const Color &other) {
	channel[0] -= other.channel[0];
	channel[1] -= other.channel[1];
	channel[2] -= other.channel[2];

	return *this;
}

Color& Color::multiply(const Color &other) {
	channel[0] *= other.channel[0];
	channel[1] *= other.channel[1];
	channel[2] *= other.channel[2];

	return *this;
}

Color& Color::divide(const Color &other) {
	channel[0] /= other.channel[0];
	channel[1] /= other.channel[1];
	channel[2] /= other.channel[2];

	return *this;
}

Color operator+(Color leftColor, Color &rightColor) {
	return leftColor.add(rightColor);
}

Color operator-(Color leftColor, Color &rightColor) {
	return leftColor.subtract(rightColor);
}

Color operator*(Color leftColor, Color &rightColor) {
	return leftColor.multiply(rightColor);
}

Color operator/(Color leftColor, Color &rightColor) {
	return leftColor.divide(rightColor);
}

Color& Color::operator+=(const Color& other) {
	return add(other);
}

Color& Color::operator-=(const Color& other) {
	return subtract(other);
}

Color& Color::operator*=(const Color& other) {
	return multiply(other);
}

Color& Color::operator/=(const Color& other) {
	return divide(other);
}

bool Color::operator==(const Color& other) {
	return m_RGB == other.m_RGB;
}

bool Color::operator!=(const Color& other) {
	return m_RGB != other.m_RGB;
}