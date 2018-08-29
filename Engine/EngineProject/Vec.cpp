#include "Vec.h"

Vec3fl::Vec3fl(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3fl::Vec3fl()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

//Vec3f::Vec3f(const Vec3f &other)

Vec3fl::Vec3fl(const Vec3fl &other)

{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3fl::operator [](int index)
{
	return v[index];
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(const Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}
