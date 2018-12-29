#pragma once

#include "vec3.h"
#include "vec4.h"

struct mat4 {
	union {
		float elements[4 * 4];
		vec4 columns[4];
	};

	mat4();
	mat4(float diagonal);

	static mat4 identity();

	mat4& multiply(const mat4 &other);
	friend mat4 operator*(mat4 left, mat4 &right);
	friend vec4 operator*(vec4 left, mat4 & right);
	mat4& operator*=(const mat4& other);

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	static mat4 translation(const vec3 &translation);
	static mat4 rotation(float angle, const vec3 &axis);
	static mat4 scale(const vec3 &scale);

};

float toRadians(float degrees);