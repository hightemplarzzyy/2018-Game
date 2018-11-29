#pragma once
#include <iostream>
#include <cmath>

struct vec3 {
	float x, y, z;

	vec3();
	vec3(const float &x, const float &y, const float &z);
	vec3(const float &x, const float &y, const float &z, bool norm);

	vec3& add(const vec3& other);
	vec3& subtract(const vec3& other);
	vec3& multiply(const vec3& other);
	vec3& divide(const vec3& other);

	friend vec3 operator+(vec3 left, const vec3& right);
	friend vec3 operator-(vec3 left, const vec3& right);
	friend vec3 operator*(vec3 left, const vec3& right);
	friend vec3 operator/(vec3 left, const vec3& right);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(const vec3& other);
	vec3& operator/=(const vec3& other);
	bool operator==(const vec3& other);
	bool operator!=(const vec3& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
};

struct vec3i {
	int x, y, z;
	vec3i();
	vec3i(const int &x, const int &y, const int &z);
};

struct vec3u {
	unsigned short x, y, z;
	vec3u();
	vec3u(const unsigned short &x, const unsigned short &y, const unsigned short &z);
};