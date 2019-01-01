#pragma once
class Vec3
{
public:
	Vec3() {};
	Vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	~Vec3() {};
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; };
	void setZ(float z) { this->z = z; }
	float getX() {
		return x;
	};
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
private:
	float x, y, z;
};
