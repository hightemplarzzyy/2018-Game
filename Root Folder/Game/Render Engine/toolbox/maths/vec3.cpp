#include "vec3.h"
vec3::vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vec3::vec3(const float &x, const float &y, const float &z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


vec3::vec3(const float &x, const float &y, const float &z, bool norm) {
	float a;
	a = sqrt(x*x + y * y + z * z);
	this->x = x / a;
	this->y = y / a;
	this->z = z / a;
}

vec3& vec3::add(const vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vec3& vec3::subtract(const vec3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vec3& vec3::multiply(const vec3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vec3& vec3::divide(const vec3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

vec3& vec3::scale(float scaleSize) {
	x *= scaleSize;
	y *= scaleSize;
	z *= scaleSize;
	return *this;
}

vec3& vec3::normalize() {
	float LEN = length();
	if (LEN != 0) {
		x /= LEN;
		y /= LEN;
		z /= LEN;
	}
	return *this;
}

float vec3::lengthSquared() {
	return x * x + y * y + z * z;
}

float vec3::length() {
	return sqrt(lengthSquared());
}

vec3 operator+(vec3 left, const vec3& right) {
	return left.add(right);
}

vec3 operator-(vec3 left, const vec3& right) {
	return left.subtract(right);
}

vec3 operator*(vec3 left, const vec3& right) {
	return left.multiply(right);
}

vec3 operator/(vec3 left, const vec3& right) {
	return left.divide(right);
}

vec3& vec3::operator+=(const vec3& other) {
	return add(other);
}

vec3& vec3::operator-=(const vec3& other) {
	return subtract(other);
}

vec3& vec3::operator*=(const vec3& other) {
	return multiply(other);
}

vec3& vec3::operator/=(const vec3& other) {
	return divide(other);
}

vec3 cross(const vec3 &left, const vec3 &right) {
	return vec3(left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x);
}

bool vec3::operator==(const vec3& other) {
	return  x == other.x && y == other.y && z == other.z;
}

bool vec3::operator!=(const vec3& other) {
	return  !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
	stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ')';
	return stream;
}



vec3i::vec3i() {
	x = 0;
	y = 0;
	z = 0;
}

vec3i::vec3i(const int &x, const int &y, const int &z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3u::vec3u() {
	x = 0;
	y = 0;
	z = 0;
}

vec3u::vec3u(const unsigned short &x, const unsigned short &y, const unsigned short &z) {
	this->x = x;
	this->y = y;
	this->z = z;
}