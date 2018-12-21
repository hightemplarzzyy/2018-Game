#include "Color.h"

Color::Color() {
	color = vec3();
}

Color::Color(float r, float g, float b) {
	color = vec3(r, g, b);
}

Color::Color(float r, float g, float b, bool convert) {
	if (convert) {
		color = vec3(r / 255.0f, g / 255.0f, b / 255.0f);
	}
	else {
		color = vec3(r, g, b);
	}
}

Color::Color(vec3 col) {
	color = vec3(col);
}

Color::Color(float r, float g, float b, float a) {
	color = vec3(r, g, b);
	this->a = a;
}

vec3 Color::getColor() {
	return color;
}

float Color::getR() {
	return color.x;
}

float Color::getG() {
	return color.y;
}

float Color::getB() {
	return color.z;
}

void Color::setColor(float r, float g, float b) {
	color = vec3(r, g, b);
}

void Color::setColor(float r, float g, float b, float a) {
	color = vec3(r, g, b);
	this->a = a;
}

void Color::setColor(vec3 col) {
	color = vec3(col);
}

void Color::setR(float r) {
	color.x = r;
}

void Color::setG(float g) {
	color.y = g;
}

void Color::setB(float b) {
	color.z = b;
}

Color Color::interpolateColors(Color color1, Color color2, float blend) {
	Color result;

	float r = (1 - blend) * color1.getR() + blend * color2.getR();
	float g = (1 - blend) * color1.getG() + blend * color2.getG();
	float b = (1 - blend) * color1.getB() + blend * color2.getB();

	result.setColor(r, g, b);
	return result;
}

Color operator+(Color leftColor, Color &rightColor) {
	float r = leftColor.getR() + rightColor.getR();
	float g = leftColor.getG() + rightColor.getG();
	float b = leftColor.getB() + rightColor.getB();

	return Color(r, g, b);
}

Color operator-(Color leftColor, Color &rightColor) {
	float r = leftColor.getR() - rightColor.getR();
	float g = leftColor.getG() - rightColor.getG();
	float b = leftColor.getB() - rightColor.getB();

	return Color(r, g, b);
}

Color operator*(Color leftColor, Color &rightColor) {
	float r = leftColor.getR() * rightColor.getR();
	float g = leftColor.getG() * rightColor.getG();
	float b = leftColor.getB() * rightColor.getB();

	return Color(r, g, b);
}

Color operator/(Color leftColor, Color &rightColor) {
	float r = leftColor.getR() / rightColor.getR();
	float g = leftColor.getG() / rightColor.getG();
	float b = leftColor.getB() / rightColor.getB();

	return Color(r, g, b);
}

Color Color::add(Color col) {
	color.x = color.x + col.getR();
	color.y = color.y + col.getG();
	color.z = color.z + col.getB();

	return *this;
}

Color Color::sub(Color col) {
	color.x = color.x - col.getR();
	color.y = color.y - col.getG();
	color.z = color.z - col.getB();

	return *this;
}

Color Color::multiply(Color col) {
	color.x = color.x * col.getR();
	color.y = color.y * col.getG();
	color.z = color.z * col.getB();

	return *this;
}

Color Color::div(Color col) {
	color.x = color.x / col.getR();
	color.y = color.y / col.getG();
	color.z = color.z / col.getB();

	return *this;
}

void Color::operator+=(Color col) {
	this->add(col);
}

void Color::operator-=(Color col) {
	this->sub(col);
}

void Color::operator*=(Color col) {
	this->multiply(col);
}

void Color::operator/=(Color col) {
	this->div(col);
}